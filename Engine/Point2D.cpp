#include "Point2D.h"
namespace Engine {
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
	bool Point2D<T>::operator==(const Point2D<T>& other)
	{
		if (_x == other._x && _y == other._y)
			return true;
		else
			return false;
	}

	template<typename T>
	Point2D<T> Point2D<T>::operator=(const Point2D<T>& other)
	{
		_x = other._x;
		_y = other._y;
		return *this;
	}

	//template class Point2D<int>;
}
