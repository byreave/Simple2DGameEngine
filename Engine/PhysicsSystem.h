#pragma once
#include "Actor.h"
namespace Physics {
	class PhysicsSystem {
	private:
		Actor * m_GameObject;
		float m_Mass;
		float m_DragCoef; //Positive
		Point2D<float> m_Force;
		Point2D<float> m_Velocity;
	public:
		PhysicsSystem(Actor * i_GameObject)
			:
			m_GameObject(i_GameObject)
		{
			m_Mass = 1.0f;
			m_DragCoef = 1.0f;
		}
		PhysicsSystem(Actor * i_GameObject, float i_Mass, float i_DragCoef)
			:
			m_GameObject(i_GameObject),
			m_Mass(i_Mass),
			m_DragCoef(i_DragCoef)
		{
		}
		void SetMass(const float i_Mass)
		{
			m_Mass = i_Mass;
		}
		inline void AddForce(Point2D<float> i_Force);
		inline void AddForce(float i_xForce, float i_yForce);
		void Update(float deltaTime);
	};
}