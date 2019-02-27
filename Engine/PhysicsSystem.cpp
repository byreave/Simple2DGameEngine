#include "PhysicsSystem.h"


//Midpoint Method
void Physics::PhysicsSystem::Update(float deltaTime)
{
	m_Force -= m_Velocity.getNormalized() * m_Velocity.getMagnitudeSqr() * m_DragCoef;

	m_Velocity = m_Velocity + (m_Force / m_Mass) * deltaTime / 2.0f;
	auto spGameObject = m_GameObject.AcquireOwnership();
	Point2D<float> newPos = spGameObject->GetPosition() + m_Velocity * deltaTime;
	spGameObject->SetPosition(newPos);

	m_Force = Point2D<float>(0.0f, 0.0f);
	//Update Drag
}

void Physics::Update(float deltaTime)
{
	for (auto phyInfo = PhysicsInfo.begin(); phyInfo != PhysicsInfo.end(); ++phyInfo)
	{
		(*phyInfo)->Update(deltaTime);
	}
}

void Physics::CleanUp()
{
	for (auto phyInfo = PhysicsInfo.begin(); phyInfo != PhysicsInfo.end(); ++phyInfo)
	{
		PhysicsSystem * pPhysicsSystem = *phyInfo;
		delete pPhysicsSystem;
	}
	PhysicsInfo.~vector();
}
