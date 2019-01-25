#include "PhysicsSystem.h"

inline void Physics::PhysicsSystem::AddForce(Point2D<float> i_Force)
{
	m_Force += i_Force;
}

inline void Physics::PhysicsSystem::AddForce(float i_xForce, float i_yForce)
{
	m_Force += Point2D<float>(i_xForce, i_yForce);
}
//Midpoint Method
void Physics::PhysicsSystem::Update(float deltaTime)
{
	m_Velocity = (m_Velocity * 2 + (m_Force / m_Mass) * deltaTime) / 2;
	Point2D<float> newPos = m_GameObject->GetPosition() + m_Velocity * deltaTime;
	m_GameObject->SetPosition(newPos);

	//Update Drag
	m_Force -= m_Velocity * m_Velocity * m_DragCoef;
}
