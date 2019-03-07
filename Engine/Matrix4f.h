#pragma once
#include <string>
#include "ConsoleLog.h"
class Matrix4f
{
public:
	Matrix4f(); //default
	Matrix4f(float * data); //with data
	Matrix4f(const Matrix4f & m); //copy
	Matrix4f & operator= (const Matrix4f& m); //assign

	~Matrix4f();

	float & operator()(unsigned int _row, unsigned int _col);
    float operator()(unsigned int _row, unsigned int _col) const;
	Matrix4f operator * (const Matrix4f & rhs) const;
	Matrix4f operator * (float rhs) const;

	Matrix4f operator / (float rhs) const;
	Matrix4f operator + (const Matrix4f & rhs) const;
	Matrix4f operator - (const Matrix4f & rhs) const;

	Matrix4f Inverse() const;
	Matrix4f Transpose() const;

private:
	float m_Mat[16];
};

Matrix4f operator *(float lhs, const Matrix4f & rhs);
inline Matrix4f::Matrix4f()
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		m_Mat[i] = 0.0f;
	}
}

inline Matrix4f::Matrix4f(float * data)
{
	memcpy(m_Mat, data, 16u * sizeof(float));
}

inline Matrix4f::Matrix4f(const Matrix4f & m)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		m_Mat[i] = m.m_Mat[i];
	}
}

inline Matrix4f & Matrix4f::operator=(const Matrix4f & m)
{
	for (unsigned int i = 0; i < 16; ++i)
	{
		m_Mat[i] = m.m_Mat[i];
	}
	return *this;
}

inline Matrix4f::~Matrix4f()
{

}

inline float & Matrix4f::operator()(unsigned int _row, unsigned int _col)
{
	if (_row > 3 && _col > 3)
	{
		DEBUG_PRINT("Error", "Row or col out of bounds!");
	}
	return m_Mat[_row * _col + _col];
}

inline float Matrix4f::operator()(unsigned int _row, unsigned int _col) const
{
	if (_row > 3 && _col > 3)
	{
		DEBUG_PRINT("Error", "Row or col out of bounds!");
	}
	return m_Mat[4 * _row + _col];
}
