#pragma once
#include <math.h>
namespace Engine {
	template <typename T = float>
	class Point2D
	{
	public:
		Point2D() {
			_x = 0;
			_y = 0;
		}
		Point2D(const T & x, const T & y) { _x = x, _y = y; }
		~Point2D(){}
		inline const Point2D<T> operator + (const Point2D<T> & other) const;
		inline const Point2D<T> operator - (const Point2D<T> & other) const;
		inline const Point2D<T> operator / (const float divider) const;
		inline const Point2D<T> operator * (const float multiplier) const;
		inline const Point2D<T> operator * (const Point2D<T> & other) const;
		inline const Point2D<T> operator *= (const float multiplier);
		inline const Point2D<T> operator *= (const Point2D<T> & other);

		inline const Point2D<T> operator /= (const float divider);

		Point2D<T>& operator += (const Point2D<T> & other);
		Point2D<T>& operator -= (const Point2D<T> & other);
		inline bool operator == (const Point2D<T> & other) const;
		Point2D<T>& operator = (const Point2D<T> & other);
		inline const Point2D<T> operator-() const;

		void setX(const T & x) { _x = x; }
		void setY(const T & y) { _y = y; }

		const T getX() const { return _x; }
		const T getY() const { return _y; }

		const T getMagnitudeSqr() { return _x * _x + _y * _y; }
		const Point2D<T> getNormalized();

	private:
		T _x;
		T _y;
	};
	template<typename T>
	inline const Point2D<T> Point2D<T>::operator+(const Point2D<T>& other) const
	{
		return Point2D<T>(_x + other._x, _y + other._y);
	}
	template<typename T>
	inline const Point2D<T> Point2D<T>::operator-(const Point2D<T>& other) const
	{
		return Point2D<T>(other._x - _x, other._y - _y);
	}

	template<typename T>
	inline const Point2D<T> Point2D<T>::operator/(const float divider) const
	{
		return Point2D<T>(_x / divider, _y / divider);
	}

	template<typename T>
	inline const Point2D<T> Point2D<T>::operator*(const float multiplier) const
	{
		return Point2D<T>(_x * multiplier, _y * multiplier);
	}

	template<typename T>
	inline const Point2D<T> Point2D<T>::operator*(const Point2D<T>& other) const
	{
		return Point2D<T>(_x * other._x, _y * other._y);
	}

	template<typename T>
	inline const Point2D<T> Point2D<T>::operator*=(const float multiplier)
	{
		_x *= multiplier;
		_y *= multiplier;
		return *this;
	}

	template<typename T>
	inline const Point2D<T> Point2D<T>::operator*=(const Point2D<T>& other)
	{
		_x *= other._x;
		_y *= other._y;
		return *this;
	}

	template<typename T>
	inline const Point2D<T> Point2D<T>::operator/=(const float divider)
	{
		this->_x /= divider;
		this->_y /= divider;
		return *this;
	}

	template<typename T>
	Point2D<T>& Point2D<T>::operator+=(const Point2D<T>& other)
	{
		this->_x += other._x;
		this->_y += other._y;
		return *this;
	}

	template<typename T>
	Point2D<T>& Point2D<T>::operator-=(const Point2D<T>& other)
	{
		this->_x -= other._x;
		this->_y -= other._y;
		return *this;
	}

	template<typename T>
	Point2D<T>& Point2D<T>::operator=(const Point2D<T>& other)
	{
		_x = other._x;
		_y = other._y;
		return *this;
	}

	template<typename T>
	const Point2D<T> Point2D<T>::operator-() const
	{
		return Point2D<T>(-_x, -_y);
	}

	template<typename T>
	inline const Point2D<T> Point2D<T>::getNormalized()
	{
		T tmpMag = getMagnitudeSqr();
		if (tmpMag == 0.0f)
			return Point2D<T>(0.0f, 0.0f);
		else
		{
			T tmpSqrtMag = sqrtf(tmpMag);

			if (tmpSqrtMag == 0)
				return Point2D<T>(0.0f, 0.0f);

			return Point2D<T>(_x / tmpSqrtMag, _y / tmpSqrtMag);
		}
	}

	template<typename T>
	inline bool Point2D<T>::operator==(const Point2D<T>& other) const
	{
		return _x == other._x && _y == other._y;
	}
}

#include "Point2D-inl.h"

