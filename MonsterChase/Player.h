#pragma once
#include "Utility.h"
class Player
{
public:
	int Lives;
	Position Pos;
	char * Name;

	Player(Position pos, int lives = 3);
	Player(char * name);
	
	~Player();

	void Move(char direction);
};

