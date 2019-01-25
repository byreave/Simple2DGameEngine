#pragma once
#include "Point2D.h"
#include "Actor.h"
using namespace Engine;
class Player : public Actor
{
public:
	Player(const Point2D<float> & pos, int lives = 3);
	Player(char * name);
	
	bool ReduceHP();
	~Player();

};

