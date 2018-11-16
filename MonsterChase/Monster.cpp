#include "Monster.h"
#include <iostream>
Monster::Monster(const char * name, int initial_num)
{
	int postfixLen = (initial_num > 26) ? 2 : 1;
	//only support 26 * 26 max
	m_name = new char[strlen(name) + 1 + postfixLen];
	memcpy(m_name, name, strlen(name));
	if (postfixLen == 1)
	{
		m_name[strlen(name)] = 'A' + initial_num;
		m_name[strlen(name)+1] = '\0';

	}
	else
	{
		m_name[strlen(name)] = 'A' + initial_num / 26;
		m_name[strlen(name)+1] = 'A' + initial_num % 26;
		m_name[strlen(name)+2] = '\0';

	}
	m_lives = 20;

	SetPosition(rand() % 50 + 50, rand() % 101);
}

Monster::Monster(const char * name, int lives, const Point2D<int>& pos)
	:Actor(name, lives, pos)
{
}

Monster::~Monster()
{
}

