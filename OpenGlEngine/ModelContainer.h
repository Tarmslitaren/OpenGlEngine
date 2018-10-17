#pragma once
#include <vector>
#include "Model.h"
#include <string>
#include "Material.h"
#include "Mesh.h"
namespace GLEN
{
	class ModelContainer
	{
	public:
		ModelContainer();
		~ModelContainer();
		Model* CreateModel(std::string path, const Material& material);
		Model* CreateModel(std::string id, Mesh* mesh);
		Model* GetModel(std::string id);
	private:
		std::vector<Model*> m_models;
	};
}

