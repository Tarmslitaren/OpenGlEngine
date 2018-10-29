#pragma once
#include <vector>
#include "Model.h"
#include <string>
#include "Material.h"
#include "CU_Vector.h"
namespace GLEN
{
	class MeshContainer
	{
	public:
		MeshContainer();
		~MeshContainer();
		int CreateMesh(std::string id, const VertexContent& data, const Material& material, VertexLayout layout, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		int CreateMesh(std::string id, const VertexContent& data, const Material& material, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		int CreateBox(std::string id, CU::Vector3f dimensions, const Material& material, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		int CreateQuad(std::string id, CU::Vector3f dimensions, const Material& material, DrawFrequency drawFrequency = GLEN::STATIC_DRAW);
		Mesh* GetMesh(int id);
	private:
		std::vector<Mesh*> m_meshes;
	};
}

