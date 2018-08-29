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
	Monster(string name, Position pos, int lives);
	~Monster();

	//Move Monster according to player's position:AI
	bool Move(Position & playerPos, int & monCount, string monName);
	void respawn(string monName, int & monCount);
};

