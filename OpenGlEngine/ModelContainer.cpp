#include "ModelContainer.h"

using namespace GLEN;

ModelContainer::ModelContainer()
{
}


ModelContainer::~ModelContainer()
{
}

int GLEN::ModelContainer::CreatePrimitive(std::string id, float * verticeData, int dataSize, VertexLayout vertexLayout, std::vector<int> textureHandles, DrawFrequency drawFrequency)
{
	//sanity check
	if (GetPrimitive(id) != nullptr)
	{
		std::cout << "trying to add primitive with same id!" << std::endl;
		return GetPrimitive(id)->GetHandle();
	}
	GLEN::Primitive* primitive = new GLEN::Primitive();
	primitive->SetVerticeData(verticeData, dataSize, vertexLayout);
	for (int handle : textureHandles)
	{
		primitive->AddTexture(handle);
	}
	int handle = primitive->Finalize(drawFrequency, id);
	m_primitives.push_back(primitive);
	return handle;
}

Primitive * GLEN::ModelContainer::GetPrimitive(std::string id)
{
	for (Primitive* primitive : m_primitives)
	{
		if (primitive->GetId() == id)
		{
			return primitive;
		}
	}
	return nullptr;
}

Primitive * GLEN::ModelContainer::GetPrimitive(int id)
{
	for (Primitive* primitive : m_primitives)
	{
		if (primitive->GetHandle() == id)
		{
			return primitive;
		}
	}
	return nullptr;
}
