#pragma once
#include "Utility.h"
using namespace std;
class Monster
{
public:

	Position Pos;//Position in the grid
	int Lives;//Lives
	char * Name;

	Monster();
	Monster(char * name, Position pos, int lives);
	~Monster();

	//Move Monster according to player's position:AI
	bool Move(Position & playerPos, int & monCount, char * monName);
	void respawn(char * monName, int & monCount);
};

