#pragma once
#include "Utility.h"
using namespace std;
class Monster
{
public:

	Position Pos;//Position in the grid
	int Lives;//Lives
	string Name;

	Monster();
	Monster(string name, Position pos, int lives = 1);
	~Monster();

	//Move Monster according to player's position:AI
	void Move(Position playerPos);
};

