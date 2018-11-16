#include "Actor.h"

Actor::~Actor()
{
	if (m_name != NULL)
		delete m_name;
}

const char * Actor::GetName() const
{
	return m_name;
}

const Point2D<int> Actor::GetPosition() const
{
	return m_pos;
}
