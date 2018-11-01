#pragma once
#include <vector>
#include "CU_Vector.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "ShaderProgram.h"
#include "Mesh.h"
#include "assimp/config.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
namespace GLEN
{
	class Model
	{
	public:
		Model(std::string path, const Material& material, bool loadInterleaved = true); //load from file
		Model(std::string id, Mesh* mesh);
		void AddMesh(Mesh* mesh) { m_meshes.push_back(mesh); }
		void Render(const CU::Matrix44f& model, RenderMode rendermode = RENDERMODE_TRIANGLES);
		void Render(const CU::Matrix44f& model, std::string shaderId, RenderMode rendermode = RENDERMODE_TRIANGLES);
		void RenderInstanced(const std::vector<CU::Matrix44f>& model , bool staticObjects = false, RenderMode rendermode = RENDERMODE_TRIANGLES);
		void SetStaticModels(const std::vector<CU::Matrix44f>& model); //no use updating positions if they are static objects.
		std::string GetId() { return m_directory; }
	private:
		void loadModel(std::string path, const Material& material);
		void processNode(aiNode *node, const aiScene *scene, const Material& material);
		Mesh* processMesh(aiMesh *mesh, const aiScene *scene, const Material& material);
		Mesh* processMeshInterleaved(aiMesh * aiMesh, const aiScene * scene, const Material& materialInput);
		std::vector<Mesh*> m_meshes; //todo: hierachy not preserved
		std::string m_directory;
		bool m_loadInterleaved;
		unsigned int m_instantiationBuffer;
	};
}

