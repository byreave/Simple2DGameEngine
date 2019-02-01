#include "GameObject.h"

GameObject::~GameObject()
{
	if (m_name != nullptr)
	{
		delete m_name;
		m_name = nullptr;
	}
}
void GameObject::SetName(const char * newName)
{
	if (m_name != nullptr)
		delete m_name;
	m_name = new char[strlen(newName)+1];
	memcpy(m_name, newName, strlen(newName) + 1);
}
