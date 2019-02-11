#pragma once
#include "GameObject.h"
#include <vector>
#include "SmartPointer.h"
namespace Physics {
	class PhysicsSystem {
	private:
		WeakPointer<GameObject> m_GameObject;
		float m_Mass;
		float m_DragCoef; //Positive
		Point2D<float> m_Force;
		Point2D<float> m_Velocity;
	public:
		PhysicsSystem(const StrongPointer<GameObject> &  i_GameObject)
			:
			m_GameObject(i_GameObject)
		{
			m_Mass = 1.0f;
			m_DragCoef = 0.2f;
		}
		PhysicsSystem(const StrongPointer<GameObject> &  i_GameObject, float i_Mass, float i_DragCoef)
			:
			m_GameObject(i_GameObject),
			m_Mass(i_Mass),
			m_DragCoef(i_DragCoef)
		{
		}
		~PhysicsSystem()
		{
			m_GameObject.~WeakPointer();
		}
		void SetMass(const float i_Mass)
		{
			m_Mass = i_Mass;
		}
		inline void AddForce(Point2D<float> i_Force);
		inline void AddForce(float i_xForce, float i_yForce);
		void Update(float deltaTime);
	};
	extern std::vector<PhysicsSystem *> PhysicsInfo;
	void Update(float deltaTime);
	void CleanUp();
}

inline void Physics::PhysicsSystem::AddForce(Point2D<float> i_Force)
{
	m_Force += i_Force;
}

inline void Physics::PhysicsSystem::AddForce(float i_xForce, float i_yForce)
{
	m_Force += Point2D<float>(i_xForce, i_yForce);
}