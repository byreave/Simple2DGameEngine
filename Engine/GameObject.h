#pragma once
#include "Point2D.h"
#include "Vector3.h"
#include <vector>
#include <string.h>
#include "SmartPointer.h"
namespace Engine
{
	class GameObject
	{
	private:
		char * m_name;
		int m_lives;
		Point2D<float>       m_pos;
		Vector3 m_rot;
		Point2D<float> m_velocity;

		GameObject(const char * i_name);
	public:
		GameObject(const char * name, int lives, const Point2D<float> & pos, const Vector3 & rotation = Vector3(0.0f, 0.0f, 0.0f), const Point2D<float> & vel = Point2D<float>(0.0f, 0.0f)) :
			m_lives(lives), m_pos(pos), m_rot(rotation), m_velocity(vel)
		{
			m_name = new char[strlen(name) + 1];
			memcpy(m_name, name, strlen(name) + 1);
		}
		~GameObject();

		inline const char * GetName() const { return m_name; }
		void SetName(const char * newName);
		inline const Point2D<float> GetPosition() const { return m_pos; }
		void SetPosition(const Point2D<float> & pos) { m_pos = pos; }
		void SetPosition(float x, float y) { m_pos.setX(x); m_pos.setY(y); }
		float GetZRotation()const { return m_rot.getZ(); }
		void SetZRotation(float zRot) { m_rot.setZ(zRot); }
		Point2D<float> GetVelocity() const { return m_velocity; }
		void SetVelocity(const Point2D<float> & vel) { m_velocity = vel; }
	};

	extern std::vector<StrongPointer<GameObject>> AllGameObjects;
}


