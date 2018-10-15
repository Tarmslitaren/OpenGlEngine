#pragma once
#include <vector>
#include "Primitive.h"
#include <string>
#include "Material.h"
namespace GLEN
{
	class ModelContainer
	{
	public:
		ModelContainer();
		~ModelContainer();
		int CreatePrimitive(std::string id, float* verticeData, int dataSize, VertexLayout vertexLayout, const Material& material, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		Primitive* GetPrimitive(std::string id);
		Primitive* GetPrimitive(int id);
	private:
		std::vector<Primitive*> m_primitives;
	};
}

