#pragma once
#include "Point2D.h"
#include "Actor.h"
using namespace Engine;
class Monster : public Actor
{
public:
	Monster(const char * name, int initial_num);
	Monster(const char * name, int lives, const Point2D<float>& pos);
	~Monster();
};

