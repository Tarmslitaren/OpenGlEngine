#include "Model.h"
#include <iostream>
#include "Engine.h"
#include "Mesh.h"
#include "Material.h"
using namespace GLEN;

GLEN::Model::Model(std::string path, const Material& material)
{
	loadModel(path, material);
}

GLEN::Model::Model(std::string id, Mesh* mesh)
{
	m_directory = id; //hmmm...
	m_meshes.push_back(mesh);
}

void GLEN::Model::Render(const CU::Matrix44f& model)
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i]->Render(model);
	}
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
	//std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<float> vertexData;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
	{
		//Vertex vertex;
		CU::Vector3f vector;
		// positions
		vertexData.push_back(aiMesh->mVertices[i].x);
		vertexData.push_back(aiMesh->mVertices[i].y);
		vertexData.push_back(aiMesh->mVertices[i].z);
		// normals
		if (aiMesh->HasNormals()) 
		{
			vertexData.push_back(aiMesh->mNormals[i].x);
			vertexData.push_back(aiMesh->mNormals[i].y);
			vertexData.push_back(aiMesh->mNormals[i].z);
		}
		// texture coordinates
		if (aiMesh->HasTextureCoords(0)) // does the mesh contain texture coordinates?
		{
			// a vertex can contain up to 8 different texture coordinates. We here make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			//todo: handle more texture coordiantes
			vertexData.push_back(aiMesh->mTextureCoords[0][i].x);
			vertexData.push_back(aiMesh->mTextureCoords[0][i].y);
		}
		if (aiMesh->HasVertexColors(0))
		{
			vertexData.push_back(aiMesh->mColors[0][i].r);
			vertexData.push_back(aiMesh->mColors[0][i].g);
			vertexData.push_back(aiMesh->mColors[0][i].b);
			vertexData.push_back(aiMesh->mColors[0][i].a);
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
			indices.push_back(face.mIndices[j]);
	}
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

	// 3. normal maps
	//std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	//textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	//std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	//textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	
	std::string id = aiMesh->mName.C_Str(); //todo: this is unsafe, there might not be a name


	VertexLayout vertexLayout;
	int stride = 0;
	int attributes = 0;
	if (aiMesh->HasPositions()) //should always be true
	{
		
		vertexLayout.locationAtrribute = attributes;
		stride += 3;
		attributes++;
	}
	if (aiMesh->HasNormals())
	{
		vertexLayout.hasNormals = true;
		vertexLayout.normalsAttribute = attributes;
		vertexLayout.normalOffset = stride;
		stride += 3;
		attributes++;
		
	}
	if (aiMesh->HasTextureCoords(0))
	{
		vertexLayout.hasTexCoords = true;
		vertexLayout.texCoordAttribute = attributes;
		vertexLayout.texCoordOffset = stride;
		stride += 2;
		attributes++;
	}
	if (aiMesh->HasVertexColors(0)) //not standard
	{
		vertexLayout.hasColor = true;
		vertexLayout.colorAtribute = attributes;
		stride += 4; //rgba
		attributes++;
		
	}
	vertexLayout.stride = stride;

	int handle = Engine::GetInstance()->GetMeshContainer().CreateMesh(id, &vertexData[0], vertexData.size(), vertexLayout, material, &indices[0], indices.size());
	Mesh* mesh = Engine::GetInstance()->GetMeshContainer().GetMesh(handle);
	// return a mesh object created from the extracted mesh data
	return mesh;
}
