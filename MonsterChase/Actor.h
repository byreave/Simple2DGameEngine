#pragma once
#include "Point2D.h"
#include <string.h>
using namespace Engine;
class Actor
{
public:
	Actor() {
	}
	Actor(const char * name, int lives, const Point2D<int> & pos) :
		m_lives(lives), m_pos(pos)
	{
		m_name = new char[strlen(name) + 1];
		memcpy(m_name, name, strlen(name) + 1);
	}
	~Actor();

	const char * GetName() const;
	void SetName(const char * newName);
	const int GetLives() const { return m_lives; }
	const Point2D<int> GetPosition() const;
	void SetPosition(const Point2D<int> & pos) { m_pos = pos; }
	void SetPosition(int x, int y) { m_pos.setX(x); m_pos.setY(y); }
	void SetLives(int lives) { m_lives = lives; }
	
protected:
	char *               m_name;
	int                  m_lives;
	Point2D<int>         m_pos;
};

