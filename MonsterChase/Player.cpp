#include "Player.h"
#include <iostream>




Player::Player(const Point2D<float> & pos, int lives)
{
	m_pos = pos;
	m_lives = lives;
}

Player::Player(char * name)
{
	m_name = new char[strlen(name) + 1];
	memcpy(m_name, name, strlen(name) + 1);
	m_lives = 3;
}

bool Player::ReduceHP()
{
	if (--m_lives > 0)
		return true;
	return false;
}

Player::~Player()
{
}
