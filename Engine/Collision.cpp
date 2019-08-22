#include "Collision.h"
#include "Matrix4f.h"
#include "Vector4.h"
#include "ConsoleLog.h"
#include "Clock.h"
#include "PhysicsSystem.h"

Engine::CollisionSystem::Collision::~Collision()
{
}

bool Engine::CollisionSystem::Collision::isColliding(const Collision & other, float deltaTime, Vector4 & CollisionNormal, float & CollisionTime)
{
	//Separating Axis Theorem
	auto bGameObject = other.m_GameObject.AcquireOwnership();
	auto aGameObject = m_GameObject.AcquireOwnership();

	Matrix4f m_Btrans = Matrix4f::GetTransformMatrix(bGameObject->GetPosition().getX(), bGameObject->GetPosition().getY(), 0.0f);
	Matrix4f m_Brots = Matrix4f::GetRotationMatrixZ(bGameObject->GetZRotation());
	Matrix4f m_Atrans = Matrix4f::GetTransformMatrix(aGameObject->GetPosition().getX(), aGameObject->GetPosition().getY(), 0.0f);
	Matrix4f m_Arots = Matrix4f::GetRotationMatrixZ(aGameObject->GetZRotation());

	Matrix4f BToWorld = m_Btrans * m_Brots;
	Matrix4f WorldToB = BToWorld.InverseSSE();

	Matrix4f AToWorld = m_Atrans * m_Arots;
	Matrix4f WorldToA = AToWorld.InverseSSE();

	Matrix4f AToB = WorldToB * AToWorld;
	Matrix4f BToA = WorldToA * BToWorld;

	float latestTClose = -FLT_MAX, earliestTOpen = FLT_MAX;

	//A projects to B
	Vector4 ACenterInB = AToB * Vector4(m_bb.m_center.getX(), m_bb.m_center.getY(), 0.0f, 1.0f);
	Vector4 AExtentsXInB = AToB * Vector4(m_bb.m_extents.getX(), 0.0f, 0.0f, 0.0f);
	Vector4 AExtentsYInB = AToB * Vector4(0.0f, m_bb.m_extents.getY(), 0.0f, 0.0f);
	Point2D<float> VelARelToB = aGameObject->GetVelocity() - bGameObject->GetVelocity();
	Vector4 VelAInB = WorldToB * Vector4(VelARelToB.getX(), VelARelToB.getY(), 0.0f, 0.0f);
	
	//B X axis
	float AProjectionOntoB_X = fabs(AExtentsXInB.x()) + fabs(AExtentsYInB.x());
	float BExtents = other.m_bb.m_extents.getX() + AProjectionOntoB_X;
	float BLeft = other.m_bb.m_center.getX() - BExtents, BRight = other.m_bb.m_center.getX() + BExtents;
	if (VelAInB.x() == 0.0f)
	{
		if (ACenterInB.x() < BLeft || ACenterInB.x() > BRight)
			return false;
	}
	else
	{
		float tclose = (BLeft - ACenterInB.x()) / VelAInB.x(), topen = (BRight - ACenterInB.x()) / VelAInB.x();
		if (topen < tclose)
		{
			float t = topen;
			topen = tclose;
			tclose = t;
		}
		if (tclose > latestTClose)
		{
			latestTClose = tclose;
			Vector4 BXinWorld = m_Brots * Vector4(1.0f, 0.0f, 0.0f);
			CollisionNormal = Vector4(-BXinWorld.x(), BXinWorld.y(), 0.0f);
		}
		if (topen < earliestTOpen)
			earliestTOpen = topen;
		if (tclose > deltaTime || topen < 0.0f)
			return false;
	}
	/*if (fabs(ACenterInB.x() - other.m_bb.m_center.getX()) > other.m_bb.m_extents.getX() + AProjectionOntoB_X)
			return false;*/
	//B Y axis
	float AProjectionOntoB_Y = fabs(AExtentsXInB.y()) + fabs(AExtentsYInB.y());
	BExtents = other.m_bb.m_extents.getY() + AProjectionOntoB_Y;
	BLeft = other.m_bb.m_center.getY() - BExtents, BRight = other.m_bb.m_center.getY() + BExtents;
	if (VelAInB.y() == 0.0f)
	{
		if (ACenterInB.y() < BLeft || ACenterInB.y() > BRight)
			return false;
	}
	else
	{
		float tclose = (BLeft - ACenterInB.y()) / VelAInB.y(), topen = (BRight - ACenterInB.y()) / VelAInB.y();
		if (topen < tclose)
		{
			float t = topen;
			topen = tclose;
			tclose = t;
		}
		if (tclose > latestTClose)
		{
			latestTClose = tclose;
			Vector4 BYinWorld = m_Brots * Vector4(0.0f, 1.0f, 0.0f);
			CollisionNormal = Vector4(-BYinWorld.x(), BYinWorld.y(), 0.0f);
		}
		if (topen < earliestTOpen)
			earliestTOpen = topen;
		if (tclose > deltaTime || topen < 0.0f)
			return false;
	}
	/*if (fabs(ACenterInB.y() - other.m_bb.m_center.getY()) > other.m_bb.m_extents.getY() + AProjectionOntoB_Y)
		return false;*/

	//B projects to A
	Vector4 BCenterInA = BToA * Vector4(other.m_bb.m_center.getX(), other.m_bb.m_center.getY(), 0.0f, 1.0f);
	Vector4 BExtentsXInA = BToA * Vector4(other.m_bb.m_extents.getX(), 0.0f, 0.0f, 0.0f);
	Vector4 BExtentsYInA = BToA * Vector4(0.0f, other.m_bb.m_extents.getY(), 0.0f, 0.0f);
	Point2D<float> VelBRelToA = -VelARelToB;
	Vector4 VelBInA = WorldToA * Vector4(VelBRelToA.getX(), VelBRelToA.getY(), 0.0f, 0.0f);
	//A X axis
	float BProjectionOntoA_X = fabs(BExtentsXInA.x()) + fabs(BExtentsYInA.x());
	float AExtents = m_bb.m_extents.getX() + BProjectionOntoA_X;
	float ALeft = m_bb.m_center.getX() - AExtents, ARight = m_bb.m_center.getX() + AExtents;
	if (VelBInA.x() == 0.0f)
	{
		if (BCenterInA.x() < ALeft || BCenterInA.x() > ARight)
			return false;
	}
	else
	{
		float tclose = (ALeft - BCenterInA.x()) / VelBInA.x(), topen = (ARight - BCenterInA.x()) / VelBInA.x();
		if (topen < tclose)
		{
			float t = topen;
			topen = tclose;
			tclose = t;
		}
		if (tclose > latestTClose)
		{
			latestTClose = tclose;
			Vector4 AXinWorld = m_Arots * Vector4(1.0f, 0.0f, 0.0f);
			CollisionNormal = Vector4(-AXinWorld.x(), AXinWorld.y(), 0.0f);
		}
		if (topen < earliestTOpen)
			earliestTOpen = topen;
		if (tclose > deltaTime || topen < 0.0f)
			return false;
	}
	/*if (fabs(BCenterInA.x() - m_bb.m_center.getX()) > m_bb.m_extents.getX() + BProjectionOntoA_X)
		return false;*/
	//A Y axis
	float BProjectionOntoA_Y = fabs(BExtentsXInA.y()) + fabs(BExtentsYInA.y());
	AExtents = m_bb.m_extents.getY() + BProjectionOntoA_Y;
	ALeft = m_bb.m_center.getY() - AExtents, ARight = m_bb.m_center.getY() + AExtents;
	if (VelBInA.y() == 0.0f)
	{
		if (BCenterInA.y() < ALeft || BCenterInA.y() > ARight)
			return false;
	}
	else
	{
		float tclose = (ALeft - BCenterInA.y()) / VelBInA.y(), topen = (ARight - BCenterInA.y()) / VelBInA.y();
		if (topen < tclose)
		{
			float t = topen;
			topen = tclose;
			tclose = t;
		}
		if (tclose > latestTClose)
		{
			latestTClose = tclose;
			Vector4 AYinWorld = m_Arots * Vector4(0.0f, 1.0f, 0.0f);
			CollisionNormal = Vector4(-AYinWorld.x(), AYinWorld.y(), 0.0f);
		}
		if (topen < earliestTOpen)
			earliestTOpen = topen;
		if (tclose > deltaTime || topen < 0.0f)
			return false;
	}
	/*if (fabs(BCenterInA.y() - m_bb.m_center.getY()) > m_bb.m_extents.getY() + BProjectionOntoA_Y)
		return false;*/
	
	if (latestTClose > earliestTOpen)
		return false;
	CollisionTime = latestTClose;
	DEBUG_PRINT("Collison Detected", "%s is Colliding %s, Normal is %f, %f, %f", aGameObject->GetName(), bGameObject->GetName(), CollisionNormal.x(), CollisionNormal.y(), CollisionNormal.z());
	return true;
}

void Engine::CollisionSystem::Update(float deltaTime)
{
	for (auto it = CollisionSystem::CollisionObjects.begin(); it != CollisionObjects.end(); ++it)
	{
		for (auto it2 = it + 1; it2 != CollisionObjects.end(); ++it2)
		{
			Vector4 collisionNormal;
			float collisionTime;
			if ((*it)->isColliding(*(*it2), deltaTime, collisionNormal, collisionTime))
			{
				auto AGameObject = (*it)->GetGameobject().AcquireOwnership();
				auto BGameObject = (*it2)->GetGameobject().AcquireOwnership();
				auto APhysicsSystem = Physics::GetPhysicsSystem(AGameObject);
				auto BPhysicsSystem = Physics::GetPhysicsSystem(BGameObject);

				if (!APhysicsSystem->IsKinematic() && BPhysicsSystem->IsKinematic())
				{
					Point2D<float> ASpeed = AGameObject->GetVelocity();
					Point2D<float> normal = Point2D<float>(collisionNormal.x(), collisionNormal.y());
					Point2D<float> NewSpeed = ASpeed - normal * (ASpeed * normal) * 2;
					AGameObject->SetVelocity(NewSpeed);
				}
				else if (APhysicsSystem->IsKinematic() && !BPhysicsSystem->IsKinematic())
				{
					Point2D<float> BSpeed = BGameObject->GetVelocity();
					Point2D<float> normal = Point2D<float>(collisionNormal.x(), collisionNormal.y());
					Point2D<float> NewSpeed = BSpeed - normal * (BSpeed * normal) * 2;
					BGameObject->SetVelocity(NewSpeed);
				}
				else if (!APhysicsSystem->IsKinematic() && !BPhysicsSystem->IsKinematic())
				{
					float AMass = APhysicsSystem->GetMass();
					float BMass = BPhysicsSystem->GetMass();
					
					if (AMass == 0.0f || BMass == 0.0f)
					{
						ConsoleLog("Error", "Mass is zero!");
						return;
					}
					Point2D<float> ASpeed = AGameObject->GetVelocity();
					Point2D<float> BSpeed = BGameObject->GetVelocity();

					Point2D<float> newASpeed = ASpeed * (AMass - BMass) / (AMass + BMass) + BSpeed * 2 * BMass / (AMass + BMass);
					Point2D<float> newBSpeed = BSpeed * (BMass - AMass) / (AMass + BMass) + ASpeed * 2 * AMass / (AMass + BMass);
					AGameObject->SetVelocity(newASpeed);
					BGameObject->SetVelocity(newBSpeed);
				}
			}
		}
	}
}

void Engine::CollisionSystem::CleanUp()
{
	for (auto it = CollisionObjects.begin(); it != CollisionObjects.end(); ++it)
	{
		Collision * col = *it;
		delete col;
	}
	CollisionObjects.~vector();
}

void Engine::CollisionSystem::Collision_UnitTest()
{
	for (int i = 0; i < 10; ++i)
	{
		GameObject* go = new GameObject("AAA", 3, Point2D<float>(-300.0f + 50.0f * i, 0.0f));
		StrongPointer<GameObject> sp(go);
		AllGameObjects.push_back(sp);
		CollisionObjects.push_back(new Collision(sp, Point2D<float>(0.0f, 0.0f), Point2D<float>(30.0f, 30.0f)));
	}
	while (true)
	{
		float deltaTime = Timing::GetTimeSinceLastCall() / 1000.0f;
		//Collision
		CollisionSystem::Update(deltaTime);
	}
}
