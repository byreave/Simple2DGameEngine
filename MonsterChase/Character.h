#pragma once
#include "Actor.h"
struct Sprite;
class Character :
	public Actor
{
private:
	Sprite * m_Sprite;
public:
	Character(const char * i_name, int i_lives, const Point2D<float> & i_Pos, Sprite * i_Sprite);
	~Character();
};

