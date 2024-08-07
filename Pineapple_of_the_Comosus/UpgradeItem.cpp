#include "UpgradeItem.h"

UpgradeItem::UpgradeItem()
{
}

bool UpgradeItem::UpgradeAble()
{
	/*if (보유골드 > 강화비용)
	{
		return true;
	}
	*/
	return false;
}

void UpgradeItem::UpgradeTurret()
{
	if (UpgradeAble())
	{
		// 해당하는 터렛 오브젝트 lv++;

		// curGold -= 터렛 강화 cost 
	}
}

void UpgradeItem::Update(float deltaTime)
{
}
