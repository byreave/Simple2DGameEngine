#pragma once
#include "Utility.h"
class Player
{
public:
	int Lives;
	Position Pos;

	Player(Position pos, int lives = 3);
	Player();
	
	~Player();

	void Move(char direction);
};

