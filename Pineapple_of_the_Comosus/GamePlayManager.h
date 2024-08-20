#pragma once
#include "../D2DEngine/Component.h"
#include "../D2DEngine/Vector.h"
#include <unordered_set>
class GameObject;
class Camera;
class BoxCollider;
class SelectTurretContainer;
class Turret;
class MainPineApple;
class SpriteRenderer;
class GamePlayManager : public Component
{
public:
	GamePlayManager() {};
	virtual ~GamePlayManager() {};

	Camera* camera;

	GameObject* dragObj = nullptr;
	SpriteRenderer* dragHighlightSpr = nullptr;
	bool isDrag = false;

	MainPineApple* pineApple = nullptr;
	GameObject* selectBoxObj = nullptr;
	BoxCollider* multiSelectBox = nullptr;
	SelectTurretContainer* selectTurrets = nullptr;
	Vector2 startPos;
	std::unordered_set<Turret*> turrets;
	bool isSelect = false;
	bool isAngle = false;

	virtual void Update(float deltaTime);

	void StartBatch(int type);
};

