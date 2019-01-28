#include "PhysicsSystem.h"


//Midpoint Method
void Physics::PhysicsSystem::Update(float deltaTime)
{
	m_Velocity = (m_Velocity * 2 + (m_Force / m_Mass) * deltaTime) / 2;
	Point2D<float> newPos = m_GameObject->GetPosition() + m_Velocity * deltaTime;
	m_GameObject->SetPosition(newPos);

	//Update Drag
	m_Force = - m_Velocity * m_Velocity * m_DragCoef;
}

void Physics::Update(float deltaTime)
{
	for (auto phyInfo = PhysicsInfo.begin(); phyInfo != PhysicsInfo.end(); ++phyInfo)
	{
		(*phyInfo)->Update(deltaTime);
	}
}