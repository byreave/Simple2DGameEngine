#pragma once
#include "Point2D.h"
#include <string.h>
using namespace Engine;
class GameObject
{
private:
	Point2D<float>       m_pos;
	char * m_name;

	GameObject(const char * i_name);
public:
	GameObject(const char * name, int lives, const Point2D<float> & pos) :
		m_pos(pos)
	{
		m_name = new char[strlen(name) + 1];
		memcpy(m_name, name, strlen(name) + 1);
	}
	~GameObject();

	inline const char * GetName() const { return m_name; }
	void SetName(const char * newName);
	inline const Point2D<float> GetPosition() const { return m_pos; }
	void SetPosition(const Point2D<float> & pos) { m_pos = pos; }
	void SetPosition(float x, float y) { m_pos.setX(x); m_pos.setY(y); }

};

