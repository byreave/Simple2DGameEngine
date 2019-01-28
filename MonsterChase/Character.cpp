#include "Character.h"



Character::Character(const char * i_name, int i_lives, const Point2D<float>& i_Pos, GLib::Sprites::Sprite * i_Sprite)
	:Actor(i_name, i_lives, i_Pos)
{
	m_Sprite = i_Sprite;
}

Character::~Character()
{
}
