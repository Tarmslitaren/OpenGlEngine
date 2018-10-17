#pragma once
#include <vector>
#include "Model.h"
#include <string>
#include "Material.h"
namespace GLEN
{
	class ModelContainer
	{
	public:
		ModelContainer();
		~ModelContainer();
		int CreateModel(std::string id, float* verticeData, int dataSize, VertexLayout vertexLayout, const Material& material, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		Model* GetModel(std::string id);
		Model* GetModel(int id);
	private:
		std::vector<Model*> m_models;
	};
}

