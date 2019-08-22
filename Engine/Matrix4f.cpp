#include "Matrix4f.h"
#include "Vector4.h"
#include "ConsoleLog.h"
#include <math.h>

#define PI 3.141593

Matrix4f Matrix4f::operator/(float rhs) const
{
	float result[16];
	for (unsigned int i = 0; i < 16; ++i)
	{
		result[i] = m_Mat[i] / rhs;
	}
	return Matrix4f(result);
}

Matrix4f Matrix4f::operator+(const Matrix4f & rhs) const
{
	float result[16];
	for (unsigned int i = 0; i < 16; ++i)
	{
		result[i] = m_Mat[i] + rhs.m_Mat[i];
	}
	return Matrix4f(result);
}

Matrix4f Matrix4f::operator-(const Matrix4f & rhs) const
{
	float result[16];
	for (unsigned int i = 0; i < 16; ++i)
	{
		result[i] = m_Mat[i] - rhs.m_Mat[i];
	}
	return Matrix4f(result);
}

Matrix4f Matrix4f::Inverse() const
{
	float inv[16], det;
	int i;

	inv[0] = m_Mat[5] * m_Mat[10] * m_Mat[15] -
		m_Mat[5] * m_Mat[11] * m_Mat[14] -
		m_Mat[9] * m_Mat[6] * m_Mat[15] +
		m_Mat[9] * m_Mat[7] * m_Mat[14] +
		m_Mat[13] * m_Mat[6] * m_Mat[11] -
		m_Mat[13] * m_Mat[7] * m_Mat[10];

	inv[4] = -m_Mat[4] * m_Mat[10] * m_Mat[15] +
		m_Mat[4] * m_Mat[11] * m_Mat[14] +
		m_Mat[8] * m_Mat[6] * m_Mat[15] -
		m_Mat[8] * m_Mat[7] * m_Mat[14] -
		m_Mat[12] * m_Mat[6] * m_Mat[11] +
		m_Mat[12] * m_Mat[7] * m_Mat[10];

	inv[8] = m_Mat[4] * m_Mat[9] * m_Mat[15] -
		m_Mat[4] * m_Mat[11] * m_Mat[13] -
		m_Mat[8] * m_Mat[5] * m_Mat[15] +
		m_Mat[8] * m_Mat[7] * m_Mat[13] +
		m_Mat[12] * m_Mat[5] * m_Mat[11] -
		m_Mat[12] * m_Mat[7] * m_Mat[9];

	inv[12] = -m_Mat[4] * m_Mat[9] * m_Mat[14] +
		m_Mat[4] * m_Mat[10] * m_Mat[13] +
		m_Mat[8] * m_Mat[5] * m_Mat[14] -
		m_Mat[8] * m_Mat[6] * m_Mat[13] -
		m_Mat[12] * m_Mat[5] * m_Mat[10] +
		m_Mat[12] * m_Mat[6] * m_Mat[9];

	inv[1] = -m_Mat[1] * m_Mat[10] * m_Mat[15] +
		m_Mat[1] * m_Mat[11] * m_Mat[14] +
		m_Mat[9] * m_Mat[2] * m_Mat[15] -
		m_Mat[9] * m_Mat[3] * m_Mat[14] -
		m_Mat[13] * m_Mat[2] * m_Mat[11] +
		m_Mat[13] * m_Mat[3] * m_Mat[10];

	inv[5] = m_Mat[0] * m_Mat[10] * m_Mat[15] -
		m_Mat[0] * m_Mat[11] * m_Mat[14] -
		m_Mat[8] * m_Mat[2] * m_Mat[15] +
		m_Mat[8] * m_Mat[3] * m_Mat[14] +
		m_Mat[12] * m_Mat[2] * m_Mat[11] -
		m_Mat[12] * m_Mat[3] * m_Mat[10];

	inv[9] = -m_Mat[0] * m_Mat[9] * m_Mat[15] +
		m_Mat[0] * m_Mat[11] * m_Mat[13] +
		m_Mat[8] * m_Mat[1] * m_Mat[15] -
		m_Mat[8] * m_Mat[3] * m_Mat[13] -
		m_Mat[12] * m_Mat[1] * m_Mat[11] +
		m_Mat[12] * m_Mat[3] * m_Mat[9];

	inv[13] = m_Mat[0] * m_Mat[9] * m_Mat[14] -
		m_Mat[0] * m_Mat[10] * m_Mat[13] -
		m_Mat[8] * m_Mat[1] * m_Mat[14] +
		m_Mat[8] * m_Mat[2] * m_Mat[13] +
		m_Mat[12] * m_Mat[1] * m_Mat[10] -
		m_Mat[12] * m_Mat[2] * m_Mat[9];

	inv[2] = m_Mat[1] * m_Mat[6] * m_Mat[15] -
		m_Mat[1] * m_Mat[7] * m_Mat[14] -
		m_Mat[5] * m_Mat[2] * m_Mat[15] +
		m_Mat[5] * m_Mat[3] * m_Mat[14] +
		m_Mat[13] * m_Mat[2] * m_Mat[7] -
		m_Mat[13] * m_Mat[3] * m_Mat[6];

	inv[6] = -m_Mat[0] * m_Mat[6] * m_Mat[15] +
		m_Mat[0] * m_Mat[7] * m_Mat[14] +
		m_Mat[4] * m_Mat[2] * m_Mat[15] -
		m_Mat[4] * m_Mat[3] * m_Mat[14] -
		m_Mat[12] * m_Mat[2] * m_Mat[7] +
		m_Mat[12] * m_Mat[3] * m_Mat[6];

	inv[10] = m_Mat[0] * m_Mat[5] * m_Mat[15] -
		m_Mat[0] * m_Mat[7] * m_Mat[13] -
		m_Mat[4] * m_Mat[1] * m_Mat[15] +
		m_Mat[4] * m_Mat[3] * m_Mat[13] +
		m_Mat[12] * m_Mat[1] * m_Mat[7] -
		m_Mat[12] * m_Mat[3] * m_Mat[5];

	inv[14] = -m_Mat[0] * m_Mat[5] * m_Mat[14] +
		m_Mat[0] * m_Mat[6] * m_Mat[13] +
		m_Mat[4] * m_Mat[1] * m_Mat[14] -
		m_Mat[4] * m_Mat[2] * m_Mat[13] -
		m_Mat[12] * m_Mat[1] * m_Mat[6] +
		m_Mat[12] * m_Mat[2] * m_Mat[5];

	inv[3] = -m_Mat[1] * m_Mat[6] * m_Mat[11] +
		m_Mat[1] * m_Mat[7] * m_Mat[10] +
		m_Mat[5] * m_Mat[2] * m_Mat[11] -
		m_Mat[5] * m_Mat[3] * m_Mat[10] -
		m_Mat[9] * m_Mat[2] * m_Mat[7] +
		m_Mat[9] * m_Mat[3] * m_Mat[6];

	inv[7] = m_Mat[0] * m_Mat[6] * m_Mat[11] -
		m_Mat[0] * m_Mat[7] * m_Mat[10] -
		m_Mat[4] * m_Mat[2] * m_Mat[11] +
		m_Mat[4] * m_Mat[3] * m_Mat[10] +
		m_Mat[8] * m_Mat[2] * m_Mat[7] -
		m_Mat[8] * m_Mat[3] * m_Mat[6];

	inv[11] = -m_Mat[0] * m_Mat[5] * m_Mat[11] +
		m_Mat[0] * m_Mat[7] * m_Mat[9] +
		m_Mat[4] * m_Mat[1] * m_Mat[11] -
		m_Mat[4] * m_Mat[3] * m_Mat[9] -
		m_Mat[8] * m_Mat[1] * m_Mat[7] +
		m_Mat[8] * m_Mat[3] * m_Mat[5];

	inv[15] = m_Mat[0] * m_Mat[5] * m_Mat[10] -
		m_Mat[0] * m_Mat[6] * m_Mat[9] -
		m_Mat[4] * m_Mat[1] * m_Mat[10] +
		m_Mat[4] * m_Mat[2] * m_Mat[9] +
		m_Mat[8] * m_Mat[1] * m_Mat[6] -
		m_Mat[8] * m_Mat[2] * m_Mat[5];

	det = m_Mat[0] * inv[0] + m_Mat[1] * inv[4] + m_Mat[2] * inv[8] + m_Mat[3] * inv[12];

	if (det == 0)
	{
		DEBUG_PRINT("Error", "Matrix cannot be inverted!");
		return Matrix4f();
	}
	det = 1.0f / det;
	for (i = 0; i < 16; i++)
		inv[i] *= det;

	return Matrix4f(inv);
}

Matrix4f Matrix4f::InverseSSE() const
{
	__m128 temp = { 0.0f };
	__m128 row0, row1, row2, row3;
	__m128 minor0, minor1, minor2, minor3;

	temp = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_11)), reinterpret_cast<const __m64 *>(&m_21));
	row1 = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_31)), reinterpret_cast<const __m64 *>(&m_41));
	row0 = _mm_shuffle_ps(temp, row1, 0x88);
	row1 = _mm_shuffle_ps(row1, temp, 0xDD);
	temp = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_13)), reinterpret_cast<const __m64 *>(&m_23));
	row3 = _mm_loadh_pi(_mm_loadl_pi(temp, reinterpret_cast<const __m64 *>(&m_33)), reinterpret_cast<const __m64 *>(&m_43));
	row2 = _mm_shuffle_ps(temp, row3, 0x88);
	row3 = _mm_shuffle_ps(row3, temp, 0xDD);

	// -----------------------------------------------
	temp = _mm_mul_ps(row2, row3);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor0 = _mm_mul_ps(row1, temp);
	minor1 = _mm_mul_ps(row0, temp);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor0 = _mm_sub_ps(_mm_mul_ps(row1, temp), minor0);
	minor1 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor1);
	minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);

	// -----------------------------------------------
	temp = _mm_mul_ps(row1, row2);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor0 = _mm_add_ps(_mm_mul_ps(row3, temp), minor0);
	minor3 = _mm_mul_ps(row0, temp);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, temp));
	minor3 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor3);
	minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

	// -----------------------------------------------
	temp = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	row2 = _mm_shuffle_ps(row2, row2, 0x4E);
	minor0 = _mm_add_ps(_mm_mul_ps(row2, temp), minor0);
	minor2 = _mm_mul_ps(row0, temp);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, temp));
	minor2 = _mm_sub_ps(_mm_mul_ps(row0, temp), minor2);
	minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

	// -----------------------------------------------
	temp = _mm_mul_ps(row0, row1);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor2 = _mm_add_ps(_mm_mul_ps(row3, temp), minor2);
	minor3 = _mm_sub_ps(_mm_mul_ps(row2, temp), minor3);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor2 = _mm_sub_ps(_mm_mul_ps(row3, temp), minor2);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, temp));

	// -----------------------------------------------
	temp = _mm_mul_ps(row0, row3);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, temp));
	minor2 = _mm_add_ps(_mm_mul_ps(row1, temp), minor2);
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor1 = _mm_add_ps(_mm_mul_ps(row2, temp), minor1);
	minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, temp));

	// -----------------------------------------------
	temp = _mm_mul_ps(row0, row2);
	temp = _mm_shuffle_ps(temp, temp, 0xB1);
	minor1 = _mm_add_ps(_mm_mul_ps(row3, temp), minor1);
	minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, temp));
	temp = _mm_shuffle_ps(temp, temp, 0x4E);
	minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, temp));
	minor3 = _mm_add_ps(_mm_mul_ps(row1, temp), minor3);

	// -----------------------------------------------
	__m128 det;

	det = _mm_mul_ps(row0, minor0);
	det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
	det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
	temp = _mm_rcp_ss(det);
	det = _mm_sub_ss(_mm_add_ss(temp, temp), _mm_mul_ss(det, _mm_mul_ss(temp, temp)));
	det = _mm_shuffle_ps(det, det, 0x00);

	minor0 = _mm_mul_ps(det, minor0);
	Matrix4f o_out;
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_11), minor0);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_13), minor0);

	minor1 = _mm_mul_ps(det, minor1);
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_21), minor1);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_23), minor1);

	minor2 = _mm_mul_ps(det, minor2);
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_31), minor2);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_33), minor2);

	minor3 = _mm_mul_ps(det, minor3);
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_41), minor3);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_43), minor3);
	return o_out;
}

Matrix4f Matrix4f::Transpose() const
{
	float result[16];
	for (int _row = 0; _row < 4; ++_row)
		for (int _col = 0; _col < 4; _col++)
			result[4 * _row + _col] = m_Mat[4 * _col + _row];
	return Matrix4f(result);
}

Matrix4f Matrix4f::operator * (const Matrix4f & rhs) const 
{
	float result[16];
	for (int _row = 0; _row < 4; ++_row)
	{
		for (int _col = 0; _col < 4; ++_col)
		{
			result[4 * _row + _col] = m_Mat[4 * _row] * rhs.m_Mat[_col] + m_Mat[4 * _row + 1] * rhs.m_Mat[_col + 4] + m_Mat[4 * _row + 2] * rhs.m_Mat[_col + 8] + m_Mat[4 * _row + 3] * rhs.m_Mat[_col + 12];
		}
	}
	return Matrix4f(result);

}
Matrix4f Matrix4f::MultiplySSE(const Matrix4f & rhs) const
{
	// load i_other
	__m128 rhs_row1 = _mm_load_ps(&rhs.m_11);
	__m128 rhs_row2 = _mm_load_ps(&rhs.m_21);
	__m128 rhs_row3 = _mm_load_ps(&rhs.m_31);
	__m128 rhs_row4 = _mm_load_ps(&rhs.m_41);

	__m128 acc;

	Matrix4f o_out;
	// (*this).col1 * i_other
	// m_11 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_11), rhs_row1);
	// m_12 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_12), rhs_row2));
	// m_13 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_13), rhs_row3));
	// m_14 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_14), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_11), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_13), acc);

	// (*this).col2 * i_other
	// m_21 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_21), rhs_row1);
	// m_22 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_22), rhs_row2));
	// m_23 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_23), rhs_row3));
	// m_24 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_24), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_21), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_23), acc);

	// (*this).col3 * i_other
	// m_31 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_31), rhs_row1);
	// m_32 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_32), rhs_row2));
	// m_33 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_33), rhs_row3));
	// m_34 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_34), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_31), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_33), acc);

	// (*this).col4 * i_other
	// m_41 * i_other.row1
	acc = _mm_mul_ps(_mm_load1_ps(&m_41), rhs_row1);
	// m_42 * i_other.row2
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_42), rhs_row2));
	// m_43 * i_other.row3
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_43), rhs_row3));
	// m_44 * i_other.row4
	acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load1_ps(&m_44), rhs_row4));

	// write result
	_mm_storel_pi(reinterpret_cast<__m64 *>(&o_out.m_41), acc);
	_mm_storeh_pi(reinterpret_cast<__m64 *>(&o_out.m_43), acc);

	return o_out;
}
Matrix4f Matrix4f::operator * (float rhs) const
{
	float result[16];
	for (unsigned int i = 0; i < 16; ++i)
	{
		result[i] = m_Mat[i] * rhs;
	}
	return Matrix4f(result);
}
Vector4 Matrix4f::operator*(const Vector4 & rhs)
{
	/*return Vector4(
		m_Mat[0] * rhs.x() + m_Mat[1] * rhs.y() + m_Mat[2] * rhs.z() + m_Mat[3] * rhs.w(),
		m_Mat[4] * rhs.x() + m_Mat[5] * rhs.y() + m_Mat[6] * rhs.z() + m_Mat[7] * rhs.w(),
		m_Mat[8] * rhs.x() + m_Mat[9] * rhs.y() + m_Mat[10] * rhs.z() + m_Mat[11] * rhs.w(),
		m_Mat[12] * rhs.x() +m_Mat[13] * rhs.y() + m_Mat[14] * rhs.z() + m_Mat[15] * rhs.w()
	);*/
	__m128 seeVec = rhs.SseVec();
	/*return Vector4(
		CalcDotProductSse(m_rows[0], seeVec),
		CalcDotProductSse(m_rows[1], seeVec),
		CalcDotProductSse(m_rows[2], seeVec),
		CalcDotProductSse(m_rows[3], seeVec)
	); */
	return Vector4(
		DotRow(0, seeVec),
		DotRow(1, seeVec),
		DotRow(2, seeVec),
		DotRow(3, seeVec)
	);
}

float Matrix4f::DotRow(int i, __m128 rhs)
{
	union
	{
		struct { float a, b, c, d; };
		__m128 vec;
	};
	vec = _mm_mul_ps(m_rows[i], rhs);
	return a + b + c + d;
}
Matrix4f operator*(float lhs, const Matrix4f & rhs)
{
	return rhs * lhs;
}

Matrix4f Matrix4f::GetTransformMatrix(float x, float y, float z)
{
	return Matrix4f(
		1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y,
		0.0f, 0.0f, 1.0f, z,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4f Matrix4f::GetRotationMatrixX(float eulerAngle)
{
	return Matrix4f(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos(eulerAngle / PI), -sin(eulerAngle / PI), 0.0f,
		0.0f, sin(eulerAngle / PI), cos(eulerAngle / PI), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4f Matrix4f::GetRotationMatrixY(float eulerAngle)
{
	return Matrix4f(
		cos(eulerAngle / PI), 0.0f, sin(eulerAngle / PI), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		-sin(eulerAngle / PI), 0.0f, cos(eulerAngle / PI), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4f Matrix4f::GetRotationMatrixZ(float eulerAngle)
{
	return Matrix4f(
		cos(eulerAngle / PI), -sin(eulerAngle / PI), 0.0f, 0.0f,
		sin(eulerAngle / PI), cos(eulerAngle / PI), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

void Matrix4f::Show() const
{
	DEBUG_PRINT("Matrix Info", "\n[%f, %f, %f, %f]\n[%f, %f, %f, %f]\n[%f, %f, %f, %f]\n[%f, %f, %f, %f]\n", m_Mat[0], m_Mat[1], m_Mat[2], m_Mat[3], m_Mat[4], m_Mat[5], m_Mat[6], m_Mat[7], m_Mat[8], m_Mat[9], m_Mat[10], m_Mat[11], m_Mat[12], m_Mat[13], m_Mat[14], m_Mat[15]);
}
