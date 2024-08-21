#pragma once
#include "../D2DEngine/Component.h"
#include "Turret.h"
class MainPineApple;
class ImageUIRenderer;
class TextUIRenderer;
class Button;
class TurretUI : public Component
{
	TurretType type = TurretType::Crossbow;
	int index = 0;

	D2D1::ColorF possible = D2D1::ColorF::Black;
	D2D1::ColorF impossible = D2D1::ColorF::Red;
public:
	TurretUI() {}
	virtual ~TurretUI() {}
	
	void SetIndex(int _index) { index = _index; }
	void SetTurret(TurretType _type) { type = _type; }

	std::wstring defaultPath;
	std::wstring upgradePath;

	Button* button = nullptr;
	ImageUIRenderer* blockImage = nullptr;
	MainPineApple* pApple = nullptr;
	TextUIRenderer* textUI = nullptr;

	int GetIndex() { return index; }
	TurretType GetTurretType() { return type; }

	virtual void Update(float deltaTime);
};

