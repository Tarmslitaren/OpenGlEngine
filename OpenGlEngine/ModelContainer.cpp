#include "ModelContainer.h"
#include "assimp/config.h"
using namespace GLEN;

ModelContainer::ModelContainer()
{
}


ModelContainer::~ModelContainer()
{
}

int GLEN::ModelContainer::CreateModel(std::string id, float * verticeData, int dataSize, VertexLayout vertexLayout, const Material& material, DrawFrequency drawFrequency)
{
	//sanity check
	if (GetModel(id) != nullptr)
	{
		std::cout << "trying to add primitive with same id!" << std::endl;
		return GetModel(id)->GetHandle();
	}
	GLEN::Model* model = new GLEN::Model();
	model->SetVerticeData(verticeData, dataSize, vertexLayout);
	model->SetMaterial(material);
	int handle = model->Finalize(drawFrequency, id);
	m_models.push_back(model);
	return handle;
}

Model * GLEN::ModelContainer::GetModel(std::string id)
{
	for (Model* primitive : m_models)
	{
		if (primitive->GetId() == id)
		{
			return primitive;
		}
	}
	return nullptr;
}

Model * GLEN::ModelContainer::GetModel(int id)
{
	for (Model* primitive : m_models)
	{
		if (primitive->GetHandle() == id)
		{
			return primitive;
		}
	}
	return nullptr;
}
