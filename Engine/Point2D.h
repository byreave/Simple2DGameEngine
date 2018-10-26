#pragma once
namespace Engine {
	template <typename T = float>
	class Point2D
	{
	public:
		Point2D() {}
		Point2D(T x, T y) { _x = x, _y = y; }
		~Point2D(){}
		Point2D<T> operator + (const Point2D<T> & other);
		Point2D<T> operator - (const Point2D<T> & other);
		Point2D<T>& operator += (const Point2D<T> & other);
		Point2D<T>& operator -= (const Point2D<T> & other);
		inline bool operator == (const Point2D<T> & other);
		Point2D<T>& operator = (const Point2D<T> & other);

		inline void setX(const T & x) { _x = x; }
		inline void setY(const T & y) { _y = y; }

		inline const T& getX() { return _x; }
		inline const T& getY() { return _y; }
	private:
		T _x;
		T _y;
	};
	template<typename T>
	Point2D<T> Point2D<T>::operator+(const Point2D<T>& other)
	{
		return Point2D<T>(_x + other._x, _y + other._y);
	}
	template<typename T>
	Point2D<T> Point2D<T>::operator-(const Point2D<T>& other)
	{
		return Point2D<T>(other._x - _x, other._y - _y);
	}

	template<typename T>
	Point2D<T>& Point2D<T>::operator+=(const Point2D<T>& other)
	{
		this._x += other._x;
		this._y += other._y;
		return *this;
	}

	template<typename T>
	Point2D<T>& Point2D<T>::operator-=(const Point2D<T>& other)
	{
		this._x -= other._x;
		this._y -= other._y;
		return *this;
	}

	template<typename T>
	Point2D<T>& Point2D<T>::operator=(const Point2D<T>& other)
	{
		_x = other._x;
		_y = other._y;
		return *this;
	}
}

#include "Point2D-inl.h"

