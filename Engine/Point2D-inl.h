#pragma once
namespace Engine {
	template<typename T>
	inline bool Point2D<T>::operator==(const Point2D<T>& other) const
	{
		return _x == other._x && _y == other._y;
	}
}