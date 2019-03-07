#pragma once
class Matrix4f;
class Vector4
{
public:
	Vector4()
	{
		_x = _y = _z = _w = 0;
	}
	Vector4(float x, float y, float z):
		_x(x), _y(y), _z(z), _w(1)
	{}
	Vector4(float x, float y, float z, float w) :
		_x(x), _y(y), _z(z), _w(w)
	{}
	~Vector4(){}

	Vector4 operator + (const Vector4 & rhs) const;
	Vector4 operator - (const Vector4 & rhs) const;
	Vector4 operator * (float rhs) const;
	Vector4 operator / (float rhs) const;
	Vector4 operator * (const Matrix4f & rhs);


	float & x() { return _x; }
	float & y() { return _y; }
	float & z() { return _z; }
	float & w() { return _w; }

	float x() const { return _x; }
	float y() const { return _y; }
	float z() const { return _z; }
	float w() const { return _w; }
private:
	float _x;
	float _y;
	float _z;
	float _w;
};

inline
Vector4 Vector4::operator + (const Vector4 & rhs) const
{
	return(Vector4(_x + rhs._x, _y + rhs._y, _z + rhs._z, _w + rhs._w));
}

inline Vector4 Vector4::operator-(const Vector4 & rhs) const
{
	return Vector4(_x - rhs._x, _y - rhs._y, _z - rhs._z, _w - rhs._w);
}

inline Vector4 Vector4::operator*(float rhs) const
{
	return Vector4(_x * rhs, _y * rhs, _z * rhs, _w * rhs);
}

inline Vector4 Vector4::operator/(float rhs) const
{
	return Vector4(_x / rhs, _y / rhs, _z / rhs, _w / rhs);
}

