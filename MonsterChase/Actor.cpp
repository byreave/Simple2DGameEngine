#include "Actor.h"
#include <iostream>
Actor::~Actor()
{
	if (m_name != nullptr)
	{
		std::cout << "CALLED ACTOR DESTRUCTOR!\n";
		delete m_name;
		m_name = nullptr;
	}
}

const char * Actor::GetName() const
{
	return m_name;
}

void Actor::SetName(const char * newName)
{
	if (m_name != nullptr)
		delete m_name;
	m_name = new char[strlen(newName)+1];
	memcpy(m_name, newName, strlen(newName) + 1);
}

const Point2D<int> Actor::GetPosition() const
{
	return m_pos;
}
