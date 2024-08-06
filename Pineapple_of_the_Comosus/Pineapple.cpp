#include "Pineapple.h"

void Pineapple::Init()
{
	for(int i = 0; i < 4; i++)
	{
		m_IsOccupied[i] = true;
		m_IsOccupied[(MAX_TURRET-1)-0] = true;
	}

}
