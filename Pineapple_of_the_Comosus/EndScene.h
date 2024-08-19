#pragma once
#include "../D2DEngine/Scene.h"

class Cutton;
class EndScene : public Scene
{
	Cutton* cuttons;
public:
	EndScene();
	~EndScene() override;

	// 씬이 활성화 될 때 호출 
	void Start() override;

	// 씬이 비활성화 될 때 호출 
	void Clear() override;

	// 씬이 업데이트 로직 
	void Update(float deltaTime) override;

	// 씬의 렌더링 로직
	void Render(D2DRenderer* _render) override;
};

