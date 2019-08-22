#pragma once
#include <string>
#include <xmmintrin.h>
#include <intrin.h>
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
	Matrix4f MultiplySSE(const Matrix4f & rhs) const;
	Matrix4f operator * (float rhs) const;
	Vector4 operator * (const Vector4 & rhs);
	__m128 Rows(int i) const { return m_rows[i]; }

	Matrix4f operator / (float rhs) const;
	Matrix4f operator + (const Matrix4f & rhs) const;
	Matrix4f operator - (const Matrix4f & rhs) const;

	Matrix4f Inverse() const;
	Matrix4f InverseSSE() const;
	Matrix4f Transpose() const;

	float DotRow(int i, __m128 rhs);
	static inline float CalcDotProductSse(__m128 x, __m128 y);
	static Matrix4f Identity();
	static Matrix4f GetTransformMatrix(float x, float y, float z);
	static Matrix4f GetRotationMatrixX(float eulerAngle);
	static Matrix4f GetRotationMatrixY(float eulerAngle);
	static Matrix4f GetRotationMatrixZ(float eulerAngle);

	void Show() const;

private:
	union
	{
		float m_Mat[16];
		__m128 m_rows[4];
		struct {
			float m_11, m_12, m_13, m_14, m_21, m_22, m_23, m_24, m_31, m_32, m_33, m_34, m_41, m_42, m_43, m_44;
		};
	};
};

Matrix4f operator *(float lhs, const Matrix4f & rhs);
inline Matrix4f::Matrix4f()
{
	/*for (unsigned int i = 0; i < 16; ++i)
	{
		m_Mat[i] = 0.0f;
	}*/
	for (unsigned int i = 0; i < 4; ++i)
		m_rows[i] = _mm_setzero_ps();
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

inline float Matrix4f::CalcDotProductSse(__m128 x, __m128 y)
{
	__m128 mulRes, shufReg, sumsReg;
	mulRes = _mm_mul_ps(x, y);

	// Calculates the sum of SSE Register - https://stackoverflow.com/a/35270026/195787
	shufReg = _mm_movehdup_ps(mulRes);        // Broadcast elements 3,1 to 2,0
	sumsReg = _mm_add_ps(mulRes, shufReg);
	shufReg = _mm_movehl_ps(shufReg, sumsReg); // High Half -> Low Half
	sumsReg = _mm_add_ss(sumsReg, shufReg);
	return  _mm_cvtss_f32(sumsReg); // Result in the lower part of the SSE Register
}

inline Matrix4f Matrix4f::Identity()
{
	return Matrix4f(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}