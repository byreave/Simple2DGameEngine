#pragma once
#include "Point2D.h" //linked error
using namespace Engine;
class Player
{
public:
	int Lives;
	Point2D<int> Pos;
	char * Name;

	Player(const Point2D<int> & pos, int lives = 3);
	Player(char * name);
	
	~Player();

	void Move(char direction);
};

