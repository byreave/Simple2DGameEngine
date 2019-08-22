#pragma once
#include <math.h>
#include <xmmintrin.h>
namespace Engine
{
	class Vector3
	{
	public:
		Vector3() {
			_x = 0;
			_y = 0;
			_z = 0;
		}
		Vector3(float x, float y, float z) :
			_x(x), _y(y), _z(z)
		{}
		~Vector3() {}
		inline const Vector3 operator + (const Vector3 & other) const;
		inline const Vector3 operator - (const Vector3 & other) const;
		inline const Vector3 operator / (const float divider) const;
		inline const Vector3 operator * (const float multiplier) const;
		inline const Vector3 operator * (const Vector3 & other) const;
		inline const Vector3 operator *= (const float multiplier);
		inline const Vector3 operator *= (const Vector3 & other);

		inline const Vector3 operator /= (const float divider);

		inline Vector3& operator += (const Vector3 & other);
		inline Vector3& operator -= (const Vector3 & other);
		inline bool operator == (const Vector3 & other) const;
		inline Vector3& operator = (const Vector3 & other);
		inline const Vector3 operator-() const;

		void setX(float x) { _x = x; }
		void setY(float y) { _y = y; }
		void setZ(float z) { _z = z; }

		const float getX() const { return _x; }
		const float getY() const { return _y; }
		const float getZ() const { return _z; }

		float getMagnitudeSqr() const { return _x * _x + _y * _y + _z * _z; }
		Vector3 getNormalized() const;

	private:
		union
		{
			struct {
				float _x, _y, _z;
			};
			__m128 m_vec;
		};
		
	};

	inline const Vector3 Vector3::operator+(const Vector3& other) const
	{
		return Vector3(_x + other._x, _y + other._y, _z + other._z);
	}

	inline const Vector3 Vector3::operator-(const Vector3& other) const
	{
		return Vector3(_x - other._x, _y - other._y, _z - other._z);
	}


	inline const Vector3 Vector3::operator/(const float divider) const
	{
		return Vector3(_x / divider, _y / divider, _z / divider);
	}


	inline const Vector3 Vector3::operator*(const float multiplier) const
	{
		return Vector3(_x * multiplier, _y * multiplier, _z * multiplier);
	}


	inline const Vector3 Vector3::operator*(const Vector3& other) const
	{
		return Vector3(_x * other._x, _y * other._y, _z * other._z);
	}


	inline const Vector3 Vector3::operator*=(const float multiplier)
	{
		_x *= multiplier;
		_y *= multiplier;
		_z *= multiplier;
		return *this;
	}


	inline const Vector3 Vector3::operator*=(const Vector3& other)
	{
		_x *= other._x;
		_y *= other._y;
		_z *= other._z;
		return *this;
	}


	inline const Vector3 Vector3::operator/=(const float divider)
	{
		_x /= divider;
		_y /= divider;
		_z /= divider;
		return *this;
	}


	inline Vector3& Vector3::operator+=(const Vector3& other)
	{
		_x += other._x;
		_y += other._y;
		_z += other._z;
		return *this;
	}


	inline Vector3& Vector3::operator-=(const Vector3& other)
	{
		_x -= other._x;
		_y -= other._y;
		_z -= other._z;
		return *this;
	}


	inline Vector3& Vector3::operator=(const Vector3& other)
	{
		_x = other._x;
		_y = other._y;
		_z = other._z;
		return *this;
	}


	inline const Vector3 Vector3::operator-() const
	{
		return Vector3(-_x, -_y, -_z);
	}

	inline bool Vector3::operator==(const Vector3& other) const
	{
		return _x == other._x && _y == other._y && _z == other._z;
	}
}



