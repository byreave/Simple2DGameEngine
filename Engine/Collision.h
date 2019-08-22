#pragma once
#include "GameObject.h"
#include "SmartPointer.h"
#include <vector>
class Vector4;
namespace Engine
{
	namespace CollisionSystem
	{
		struct BoundingBox
		{
			Point2D<float> m_center;
			Point2D<float> m_extents;
		};
		class Collision
		{
		private:
			WeakPointer<GameObject> m_GameObject;
			BoundingBox m_bb;
		public:
			Collision(StrongPointer<GameObject> gameObject, Point2D<float> center, Point2D<float> extents) :
				m_GameObject(gameObject)
			{
				m_bb.m_center = center;
				m_bb.m_extents = extents;
			}
			~Collision();
			bool isColliding(const Collision & other, float deltaTime, Vector4 &, float &);
			WeakPointer<GameObject> GetGameobject() { return m_GameObject; }
		};

		void Update(float deltaTime);
		void CleanUp();
		//UnitTest
		void Collision_UnitTest();
		extern std::vector<Collision *> CollisionObjects;
	}
}

