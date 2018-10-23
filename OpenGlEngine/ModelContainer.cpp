#include "ModelContainer.h"
#include "assimp/config.h"
using namespace GLEN;

ModelContainer::ModelContainer()
{
}


ModelContainer::~ModelContainer()
{
}

Model* GLEN::ModelContainer::CreateModel(std::string path, const Material& material )
{
	//sanity check
	if (GetModel(path) != nullptr)
	{
		std::cout << "trying to add model with same id!" << std::endl;
		return GetModel(path);
	}
	GLEN::Model* model = new GLEN::Model(path, material);
	//model->SetMaterial(material);
	m_models.push_back(model);
	return model;
}

Model * GLEN::ModelContainer::CreateModel(std::string id, Mesh* mesh)
{
	//sanity check
	if (GetModel(id) != nullptr)
	{
		std::cout << "trying to add model with same id!" << std::endl;
		return GetModel(id);
	}
	GLEN::Model* model = new GLEN::Model(id, mesh);
	m_models.push_back(model);
	return model;
}

Model * GLEN::ModelContainer::GetModel(std::string id)
{
	for (Model* model : m_models)
	{
		if (model->GetId() == id)
		{
			return model;
		}
	}
	return nullptr;
}