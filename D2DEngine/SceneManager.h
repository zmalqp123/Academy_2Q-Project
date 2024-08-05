#pragma once
#include <unordered_map>
#include <string>
using namespace std;
class Scene;
class SceneManager
{
private:
	SceneManager() {};
	~SceneManager() {};

	std::unordered_map<string, Scene*> scenes;
	Scene* curScene = nullptr;
public:

	void Init();
	void AddScene(string sceneName, Scene* scene);
	void RemoveScene(string sceneName);
	void LoadScene(string sceneName);

	string GetCurSceneKey();
	Scene* GetCurSceneValue();
};

