#pragma once
#include <vector>
#include <string>

class GameObject;
class gamePopup
{
public:
	std::vector<GameObject*> victory;
	std::vector<GameObject*> defeat;

	void victoryUIon();
	void victoryUIoff();

	void defeatUIon();
	void defeatUIoff();
};

