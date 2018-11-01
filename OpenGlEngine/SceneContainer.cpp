#include "SceneContainer.h"
#include "ErrorHandler.h"
using namespace GLEN;


SceneContainer::SceneContainer()
{
	//AddScene(); //need at least one default scene
}


SceneContainer::~SceneContainer()
{
	//todo: not doing any cleanup whatsoever. bad bad bad.
}

Scene& GLEN::SceneContainer::AddScene()
{
	Scene* scene = new Scene();
	m_scenes.push_back(scene);
	return *scene;
}

void GLEN::SceneContainer::SetCurrentScene(int index)
{
	if (index < m_scenes.size())
	{
		m_currentScene = index;
		m_scenes.at(m_currentScene)->SetActive();
	}
	else
	{
		ErrorHandler::Output("SetCurrentScene: Scene Index Out of bounds!");
	}
}

void GLEN::SceneContainer::SetCurrentScene(Scene & scene)
{
	for (int i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] == &scene)
		{
			m_currentScene = i;
			m_scenes.at(m_currentScene)->SetActive();
			return;
		}
	}
	m_currentScene = m_scenes.size();
	m_scenes.push_back(&scene); //if scene is not in containerm then add it. This could be dangerous if the input parameter is on the stack and goes out of scope. (which is why to use smart pointers.
	m_scenes.at(m_currentScene)->SetActive();
}
