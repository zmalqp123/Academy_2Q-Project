#pragma once
#define MAX_TURRET 18

#include "../D2DEngine/GameObject.h"
class Turret;
class Pineapple : public GameObject
{	
private:

	float MaxHp = 100;
	int pineAppleNum = 1;
	int level = 1;
	Turret* m_Turrets[MAX_TURRET];
	bool m_IsOccupied[MAX_TURRET] = { false, }; //터렛 추가 삭제 할때 꼭 같이 수정해야함!
public:
	Pineapple() = default;
	~Pineapple() = default;

	void Init() override;

	void SetOccupied(int index, bool isOccupied) { m_IsOccupied[index] = isOccupied; }
	bool GetOccupied(int index) { return m_IsOccupied[index]; }

	void SetTurret(int index, Turret* turret) {
		if (!GetOccupied(index))
		{	
			m_Turrets[index] = turret;
			SetOccupied(index, true);
		}
	}
	Turret* GetTurret(int index) { return m_Turrets[index]; }

	void SetMaxHp(float hp) { MaxHp = hp; }
	int GetMaxHp() { return MaxHp; }

	bool IsGameOver() { return (GetMaxHp()<=0); };
};

