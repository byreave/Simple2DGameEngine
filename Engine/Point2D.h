#pragma once
namespace Engine {
	template <typename T = float>
	class Point2D
	{
	public:
		Point2D() {}
		Point2D(const T & x, const T & y) { _x = x, _y = y; }
		~Point2D(){}
		inline const Point2D<T> operator + (const Point2D<T> & other) const;
		inline const Point2D<T> operator - (const Point2D<T> & other) const;
		Point2D<T>& operator += (const Point2D<T> & other);
		Point2D<T>& operator -= (const Point2D<T> & other);
		inline bool operator == (const Point2D<T> & other) const;
		Point2D<T>& operator = (const Point2D<T> & other);
		inline const Point2D<T> operator-() const;

		void setX(const T & x) { _x = x; }
		void setY(const T & y) { _y = y; }

		const T getX() const { return _x; }
		const T getY() const { return _y; }
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

	template<typename T>
	const Point2D<T> Point2D<T>::operator-() const
	{
		return Point2D<T>(-_x, -_y);
	}
}

#include "Point2D-inl.h"

