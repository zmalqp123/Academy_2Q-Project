#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
void SceneManager::Init()
{
	if (scenes.empty()) {
		Scene* scene = new Scene();
		scenes.insert(make_pair("Default", scene));

		auto camera = scene->CreateGameObject<GameObject>();
		auto pCam = camera->CreateComponent<Camera>();
		scene->SetMainCamera(pCam);
		
		curScene = scene;
	}
}

void SceneManager::AddScene(string sceneName, Scene* scene)
{
	scenes.insert(make_pair(sceneName.c_str(), scene));
}

void SceneManager::RemoveScene(string sceneName)
{
	scenes.erase(sceneName);
}

void SceneManager::LoadScene(string sceneName)
{
	//curScene->Release
}

string SceneManager::GetCurSceneKey()
{
	return string();
}

Scene* SceneManager::GetCurSceneValue()
{
	return nullptr;
}
