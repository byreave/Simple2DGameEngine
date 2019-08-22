#include "PhysicsSystem.h"
#include "ConsoleLog.h"

//Midpoint Method
void Engine::Physics::PhysicsSystem::Update(float deltaTime)
{
	auto sp = m_GameObject.AcquireOwnership();
	Point2D<float> OldVel = sp->GetVelocity();
	Point2D<float> drag = -OldVel.getNormalized() * OldVel.getMagnitudeSqr() * m_DragCoef;
	//m_Force -= m_Velocity.getNormalized() * m_Velocity.getMagnitudeSqr() * m_DragCoef;
	sp->SetVelocity(OldVel + ((m_Force + drag) / m_Mass) * deltaTime / 2.0f);
	Point2D<float> newPos = sp->GetPosition() + sp->GetVelocity() * deltaTime;
	sp->SetPosition(newPos);

}

void Engine::Physics::Update(float deltaTime)
{
	for (auto phyInfo = PhysicsInfo.begin(); phyInfo != PhysicsInfo.end(); ++phyInfo)
	{
		(*phyInfo)->Update(deltaTime);
	}
}

void Engine::Physics::CleanUp()
{
	for (auto phyInfo = PhysicsInfo.begin(); phyInfo != PhysicsInfo.end(); ++phyInfo)
	{
		PhysicsSystem * pPhysicsSystem = *phyInfo;
		delete pPhysicsSystem;
	}
	PhysicsInfo.~vector();
}

Engine::Physics::PhysicsSystem * Engine::Physics::GetPhysicsSystem(const StrongPointer<GameObject>& gameObject)
{
	for (auto phyInfo = PhysicsInfo.begin(); phyInfo != PhysicsInfo.end(); ++phyInfo)
	{
		if((*phyInfo)->GetGameobject() == gameObject)
			return *phyInfo;
	}
	return nullptr;
}

void Engine::Physics::PhysicsSystem_UnitTest()
{
	//initialize 10 physics component
	for (int i = 0; i < 10; ++i)
	{
		GameObject* go = new GameObject("AAA", 3, Point2D<float>(-300.0f + 50.0f * i, 0.0f));
		PhysicsInfo.push_back(new PhysicsSystem(StrongPointer<GameObject>(go)));
	}
}
