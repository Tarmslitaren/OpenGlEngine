#pragma once
#include <vector>
#include "Primitive.h"
#include <string>
namespace GLEN
{
	class ModelContainer
	{
	public:
		ModelContainer();
		~ModelContainer();
		int CreatePrimitive(std::string id, float* verticeData, int dataSize, VertexLayout vertexLayout, std::vector<int> textureHandles, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		Primitive* GetPrimitive(std::string id);
		Primitive* GetPrimitive(int id);
	private:
		std::vector<Primitive*> m_primitives;
	};
}

