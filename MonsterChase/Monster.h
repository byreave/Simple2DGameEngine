#pragma once
#include "Point2D.h"
using namespace std;
using namespace Engine;
class Monster
{
public:

	Point2D<int> Pos;//Position in the grid
	int Lives;//Lives
	char * Name;

	Monster();
	Monster(char * name, Point2D<int> pos, int lives);
	~Monster();

	//Move Monster according to player's position:AI
	bool Move(Point2D<int> & playerPos, int & monCount, char * monName);
	void respawn(char * monName, int & monCount);
};

