#include "Vector4.h"
#include "Matrix4f.h"

Vector4 Vector4::operator * (const Matrix4f & rhs)
{
	return Vector4(
		_x * rhs(0, 0) + _y * rhs(1, 0) + _z * rhs(2, 0) + _w * rhs(3, 0),
		_x * rhs(0, 1) + _y * rhs(1, 1) + _z * rhs(2, 1) + _w * rhs(3, 1),
		_x * rhs(0, 2) + _y * rhs(1, 2) + _z * rhs(2, 2) + _w * rhs(3, 2),
		_x * rhs (0, 3) + _y * rhs(1, 3) + _z * rhs(2, 3) + _w * rhs(3, 3)
		);
}