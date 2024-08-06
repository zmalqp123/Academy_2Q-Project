#include "Pineapple.h"

void Pineapple::Init()
{	
	if (level == 1) {
		for (int i = 0; i < 4; i++)
		{

			m_IsOccupied[i] = true;
			m_IsOccupied[(MAX_TURRET - 1) - 0] = true;
		}
	}
	else if (level == 2) {
		m_IsOccupied[0] = true;
		m_IsOccupied[3] = true;
		m_IsOccupied[14] = true;
		m_IsOccupied[17] = true;
	}
	

}
