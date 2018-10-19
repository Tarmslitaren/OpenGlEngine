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
		Model(std::string path); //load from file
		Model(std::string id, Mesh* mesh);
		void AddMesh(Mesh* mesh) { m_meshes.push_back(mesh); }
		void Render();
		std::string GetId() { return m_directory; }
	private:
		void loadModel(std::string path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh* processMesh(aiMesh *mesh, const aiScene *scene);

		std::vector<Mesh*> m_meshes;
		std::string m_directory;
	};
}

