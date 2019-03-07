#pragma once
#include <string>
#include "ConsoleLog.h"
class Vector4;
class Matrix4f
{
public:
	Matrix4f(); //default
	Matrix4f(float i00, float i01, float i02, float i03, float i10, float i11, float i12, float i13, float i20, float i21, float i22, float i23, float i30, float i31, float i32, float i33);
	Matrix4f(float * data); //with data
	Matrix4f(const Matrix4f & m); //copy
	Matrix4f & operator= (const Matrix4f& m); //assign

	~Matrix4f();

	float & operator()(unsigned int _row, unsigned int _col);
    float operator()(unsigned int _row, unsigned int _col) const;
	Matrix4f operator * (const Matrix4f & rhs) const;
	Matrix4f operator * (float rhs) const;
	Vector4 operator * (const Vector4 & rhs);

	Matrix4f operator / (float rhs) const;
	Matrix4f operator + (const Matrix4f & rhs) const;
	Matrix4f operator - (const Matrix4f & rhs) const;

	Matrix4f Inverse() const;
	Matrix4f Transpose() const;

	static Matrix4f Identity();

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

inline Matrix4f::Matrix4f(float i00, float i01, float i02, float i03, float i10, float i11, float i12, float i13, float i20, float i21, float i22, float i23, float i30, float i31, float i32, float i33)
{
	m_Mat[0] = i00;
	m_Mat[1] = i01;
	m_Mat[2] = i02;
	m_Mat[3] = i03;
	m_Mat[4] = i10;
	m_Mat[5] = i11;
	m_Mat[6] = i12;
	m_Mat[7] = i13;
	m_Mat[8] = i20;
	m_Mat[9] = i21;
	m_Mat[10] = i22;
	m_Mat[11] = i23;
	m_Mat[12] = i30;
	m_Mat[13] = i31;
	m_Mat[14] = i32;
	m_Mat[15] = i33;
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

inline Matrix4f Matrix4f::Identity()
{
	return Matrix4f(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}