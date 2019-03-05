#include "PhysicsSystem.h"
#include "ConsoleLog.h"

//Midpoint Method
void Physics::PhysicsSystem::Update(float deltaTime)
{
	Point2D<float> drag = - m_Velocity.getNormalized() * m_Velocity.getMagnitudeSqr() * m_DragCoef;
	//m_Force -= m_Velocity.getNormalized() * m_Velocity.getMagnitudeSqr() * m_DragCoef;
	DEBUG_PRINT("DBG", "drag x: %f, drag y: %f", drag.getX(), drag.getY());
	m_Velocity = m_Velocity + ((m_Force + drag) / m_Mass) * deltaTime / 2.0f;
	Point2D<float> newPos = m_GameObject->GetPosition() + m_Velocity * deltaTime;
	m_GameObject->SetPosition(newPos);

	//m_Force = Point2D<float>(0.0f, 0.0f);
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
