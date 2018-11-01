#pragma once
#include "Scene.h"
#include <vector>
namespace GLEN
{
	class SceneContainer
	{
	public:
		SceneContainer();
		~SceneContainer();
		Scene& AddScene();//returns the index to the scene
		void SetCurrentScene(int index);
		void SetCurrentScene(Scene& scene);
		Scene& GetCurrentScene() { return *m_scenes.at(m_currentScene); }
	private:
		std::vector<Scene*> m_scenes;
		//todo: use smart pointers everywhere;
		int m_currentScene = 0;


	};
}

