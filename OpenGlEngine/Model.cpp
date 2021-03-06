#include "Model.h"
#include <iostream>
#include "Engine.h"
#include "Mesh.h"
#include "Material.h"
using namespace GLEN;

GLEN::Model::Model(std::string path, const Material& material, bool loadInterleaved)
{
	m_loadInterleaved = loadInterleaved;
	loadModel(path, material);

	//instancing buffer init
	glGenBuffers(1, &m_instantiationBuffer);


	//init instantiation
	glBindBuffer(GL_ARRAY_BUFFER, m_instantiationBuffer);

	GLsizei vec4Size = sizeof(CU::Vector4f);
	glEnableVertexAttribArray(VERTEX_LAYOUT_INSTANCE_MATRIX);
	glVertexAttribPointer(VERTEX_LAYOUT_INSTANCE_MATRIX, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
	glEnableVertexAttribArray(VERTEX_LAYOUT_INSTANCE_MATRIX + 1);
	glVertexAttribPointer(VERTEX_LAYOUT_INSTANCE_MATRIX + 1, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
	glEnableVertexAttribArray(VERTEX_LAYOUT_INSTANCE_MATRIX + 2);
	glVertexAttribPointer(VERTEX_LAYOUT_INSTANCE_MATRIX + 2, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
	glEnableVertexAttribArray(VERTEX_LAYOUT_INSTANCE_MATRIX + 3);
	glVertexAttribPointer(VERTEX_LAYOUT_INSTANCE_MATRIX + 3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

	glVertexAttribDivisor(VERTEX_LAYOUT_INSTANCE_MATRIX, 1);
	glVertexAttribDivisor(VERTEX_LAYOUT_INSTANCE_MATRIX + 1, 1);
	glVertexAttribDivisor(VERTEX_LAYOUT_INSTANCE_MATRIX + 2, 1);
	glVertexAttribDivisor(VERTEX_LAYOUT_INSTANCE_MATRIX + 3, 1);
}

GLEN::Model::Model(std::string id, Mesh* mesh)
{
	m_directory = id; //hmmm...
	m_meshes.push_back(mesh);
}

void GLEN::Model::Render(const CU::Matrix44f& model, RenderMode rendermode)
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i]->Render(model, rendermode);
	}
}

void GLEN::Model::Render(const CU::Matrix44f & model, std::string shaderId, RenderMode rendermode)
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i]->Render(model, shaderId, rendermode);
	}
}

void GLEN::Model::RenderInstanced(const std::vector<CU::Matrix44f>& models, bool staticObjects, RenderMode rendermode)
{

	glBindBuffer(GL_ARRAY_BUFFER, m_instantiationBuffer);
	if (!staticObjects) {
		int size = models.size() * sizeof(CU::Matrix44f);
		glBufferData(GL_ARRAY_BUFFER, size, &models[0], GL_STATIC_DRAW);
	}

	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i]->RenderInstanced(models);
	}
}

void GLEN::Model::SetStaticModels(const std::vector<CU::Matrix44f>& models)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_instantiationBuffer);
	int size = models.size() * sizeof(CU::Matrix44f);
	glBufferData(GL_ARRAY_BUFFER, size, &models[0], GL_STATIC_DRAW);
}

void GLEN::Model::loadModel(std::string path, const Material& material)
{

	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}
	// retrieve the directory path of the filepath
	m_directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene, material);

	//other useful options:
	//aiProcess_GenNormals: actually creates normals for each vertex if the model didn't contain normal vectors.
	//aiProcess_SplitLargeMeshes : splits large meshes into smaller sub - meshes which is useful if your rendering has a maximum number of vertices allowed and can only process smaller meshes.
	//aiProcess_OptimizeMeshes : actually does the reverse by trying to join several meshes into one larger mesh, reducing drawing calls for optimization.
	//http://assimp.sourceforge.net/lib_html/postprocess_8h.html
}

void GLEN::Model::processNode(aiNode * node, const aiScene * scene, const Material& material)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene, material));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, material);
	}
}

Mesh* GLEN::Model::processMesh(aiMesh * aiMesh, const aiScene * scene, const Material& materialInput)
{

	// process materials
	aiMaterial* aiMaterial = scene->mMaterials[aiMesh->mMaterialIndex];

	GLEN::Material material(materialInput);
	//todo: supply material definition (including uniform value pairs) to this, so we can set shader and so forth per mesh/model

	int textureCount = 0;
	for (unsigned int i = 0; i < aiMaterial->GetTextureCount(aiTextureType_DIFFUSE); i++, textureCount++)
	{
		aiString str;
		aiMaterial->GetTexture(aiTextureType_DIFFUSE, i, &str);
		std::string filename = m_directory + '/' + str.C_Str();
		material.AddDiffuseTexture(filename, textureCount);

	}
	for (unsigned int i = 0; i < aiMaterial->GetTextureCount(aiTextureType_SPECULAR); i++, textureCount++)
	{
		aiString str;
		aiMaterial->GetTexture(aiTextureType_SPECULAR, i, &str);
		std::string filename = m_directory + '/' + str.C_Str();
		material.AddSpecularTexture(filename, textureCount);

	}
	//todo: support reflection maps (use ambient map for that)

	// 3. normal maps
	//std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	//std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	if (m_loadInterleaved)
	{
		return processMeshInterleaved(aiMesh, scene, material);
	}

	VertexContent content;
	//todo: bajs: this wont work as aiMesh stores vectors and not raw floats: will need to loop anyway :(
	/*content.positions.insert(content.positions.end(), &aiMesh->mVertices[0], &aiMesh->mVertices[aiMesh->mNumVertices]);
	if (aiMesh->HasNormals())
	{
		content.normals.insert(content.normals.end(), &aiMesh->mVertices[0], &aiMesh->mNormals[aiMesh->mNumVertices]);
	}
	if (aiMesh->HasTextureCoords(0))
	{
		content.texCoords.insert(content.texCoords.end(), &aiMesh->mTextureCoords[0][0], &aiMesh->mTextureCoords[0][aiMesh->mNumVertices]);
	}
	if (aiMesh->HasVertexColors(0))
	{
		content.colors.insert(content.colors.end(), &aiMesh->mColors[0][0], &aiMesh->mColors[0][aiMesh->mNumVertices]);
	}*/

	// now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	std::vector<unsigned int> indices;
	for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
	{
		aiFace face = aiMesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	std::string id = aiMesh->mName.C_Str(); //todo: this is unsafe, there might not be a name
	int handle = Engine::GetInstance()->GetMeshContainer().CreateMesh(id, content, material);
	Mesh* mesh = Engine::GetInstance()->GetMeshContainer().GetMesh(handle);

	// return a mesh object created from the extracted mesh data
	return mesh;
}

Mesh * GLEN::Model::processMeshInterleaved(aiMesh * aiMesh, const aiScene * scene, const Material & material)
{

	VertexContent content;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
	{
		//Vertex vertex;
		CU::Vector3f vector;
		// positions
		content.interleavedVertices.push_back(aiMesh->mVertices[i].x);
		content.interleavedVertices.push_back(aiMesh->mVertices[i].y);
		content.interleavedVertices.push_back(aiMesh->mVertices[i].z);
		// normals
		if (aiMesh->HasNormals())
		{
			content.interleavedVertices.push_back(aiMesh->mNormals[i].x);
			content.interleavedVertices.push_back(aiMesh->mNormals[i].y);
			content.interleavedVertices.push_back(aiMesh->mNormals[i].z);
		}
		// texture coordinates
		if (aiMesh->HasTextureCoords(0)) // does the mesh contain texture coordinates?
		{
			// a vertex can contain up to 8 different texture coordinates. We here make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			//todo: handle more texture coordiantes
			content.interleavedVertices.push_back(aiMesh->mTextureCoords[0][i].x);
			content.interleavedVertices.push_back(aiMesh->mTextureCoords[0][i].y);
		}
		if (aiMesh->HasVertexColors(0))
		{
			content.interleavedVertices.push_back(aiMesh->mColors[0][i].r);
			content.interleavedVertices.push_back(aiMesh->mColors[0][i].g);
			content.interleavedVertices.push_back(aiMesh->mColors[0][i].b);
			content.interleavedVertices.push_back(aiMesh->mColors[0][i].a);
		}
		// tangent
		//vector.x = mesh->mTangents[i].x;
		//vector.y = mesh->mTangents[i].y;
		//vector.z = mesh->mTangents[i].z;
		//vertex.Tangent = vector;
		// bitangent
		//vector.x = mesh->mBitangents[i].x;
		//vector.y = mesh->mBitangents[i].y;
		//vector.z = mesh->mBitangents[i].z;
		//vertex.Bitangent = vector;
	}
	// now walk through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
	{
		aiFace face = aiMesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			content.indexes.push_back(face.mIndices[j]);
	}

	VertexLayout vertexLayout;
	int stride = 0;
	int attributes = 0;
	if (aiMesh->HasPositions()) //should always be true
	{

		stride += 3;
		attributes++;
	}
	if (aiMesh->HasNormals())
	{
		vertexLayout.hasNormals = true;
		vertexLayout.normalOffset = stride;
		stride += 3;
		attributes++;

	}
	if (aiMesh->HasTextureCoords(0))
	{
		vertexLayout.hasTexCoords = true;
		vertexLayout.texCoordOffset = stride;
		stride += 2;
		attributes++;
	}
	if (aiMesh->HasVertexColors(0)) //not standard
	{
		vertexLayout.hasColor = true;
		stride += 4; //rgba
		attributes++;

	}
	vertexLayout.stride = stride;

	content.vertexLayout = vertexLayout;

	std::string id = aiMesh->mName.C_Str(); //todo: this is unsafe, there might not be a name


	int handle = Engine::GetInstance()->GetMeshContainer().CreateMesh(id, content, material);
	Mesh* mesh = Engine::GetInstance()->GetMeshContainer().GetMesh(handle);
	return mesh;
}
