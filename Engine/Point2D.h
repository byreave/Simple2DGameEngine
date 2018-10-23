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
		bool operator == (const Point2D<T> & other);
		Point2D<T>& operator=(const Point2D<T> & other);

		void setX(const T & x) { _x = x; }
		void setY(const T & y) { _y = y; }

		const T& getX() { return _x; }
		const T& getY() { return _y; }
	private:
		T _x;
		T _y;
	};
}

