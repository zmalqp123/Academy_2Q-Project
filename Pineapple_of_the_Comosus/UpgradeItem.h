#pragma
#include "../D2DEngine/Component.h"

class ImageUIRenderer;
class UpgradeItem : public Component
{
private:
public:
	UpgradeItem();
	// 터렛이 설치된 타일 좌클릭 

	// 강화 가능 여부 체크 
	bool UpgradeAble();

	// 터렛 강화
	void UpgradeTurret();

	// 강화 상태 업데이트 
	void Update(float deltaTime);
};

