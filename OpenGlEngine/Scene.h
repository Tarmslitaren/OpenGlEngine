#pragma once
#include <vector>
#include "Primitive.h"
namespace GLEN
{
	class Scene
	{
	public:
		Scene();
		~Scene();
		void Render();
		void Update(float deltaTime);
		void AddPrimitive(Primitive* primitive) { m_primitives.push_back(primitive); }
	private:
		std::vector<Primitive*> m_primitives; //todo: in future abstract to instance that can be any type of model or primitive
	};
}

