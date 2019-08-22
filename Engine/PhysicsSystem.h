#pragma once
#include "GameObject.h"
#include <vector>
#include "SmartPointer.h"
namespace Engine {
	namespace Physics {
		class PhysicsSystem {
		private:
			WeakPointer<GameObject> m_GameObject;
			bool isKinematic;
			float m_Mass;
			float m_DragCoef; //Positive
			Point2D<float> m_Force;
			//Point2D<float> m_Velocity;
		public:
			PhysicsSystem(const StrongPointer<GameObject> &  i_GameObject)
				:
				m_GameObject(i_GameObject)
			{
				m_Mass = 1.0f;
				m_DragCoef = 0.02f;
			}
			PhysicsSystem(const StrongPointer<GameObject> &  i_GameObject, float i_Mass, float i_DragCoef, bool i_iskinematic = false)
				:
				m_GameObject(i_GameObject),
				m_Mass(i_Mass),
				m_DragCoef(i_DragCoef),
				isKinematic(i_iskinematic)
			{
			}
			~PhysicsSystem()
			{
			}
			void SetMass(const float i_Mass)
			{
				m_Mass = i_Mass;
			}
			float GetMass() const { return m_Mass; };
			WeakPointer<GameObject> GetGameobject() const { return m_GameObject; }
			inline void AddForce(Point2D<float> i_Force);
			inline void AddForce(float i_xForce, float i_yForce);
			void Update(float deltaTime);
			bool IsKinematic() const { return isKinematic; }
		};
		extern std::vector<PhysicsSystem *> PhysicsInfo;
		void Update(float deltaTime);
		void CleanUp();
		PhysicsSystem * GetPhysicsSystem(const StrongPointer<GameObject> & gameObject);
		//UnitTest
		void PhysicsSystem_UnitTest();
	}

}

inline void Engine::Physics::PhysicsSystem::AddForce(Point2D<float> i_Force)
{
	m_Force += i_Force;
}

inline void Engine::Physics::PhysicsSystem::AddForce(float i_xForce, float i_yForce)
{
	m_Force += Point2D<float>(i_xForce, i_yForce);
}