#pragma once
#include "Actor.h"
#include "GLib.h"
class Character :
	public Actor
{
private:
	GLib::Sprites::Sprite * m_Sprite;
public:
	Character(const char * i_name, int i_lives, const Point2D<float> & i_Pos, GLib::Sprites::Sprite * i_Sprite);
	GLib::Sprites::Sprite * GetSprite()
	{
		return m_Sprite;
	}
	~Character();
};

