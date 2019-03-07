#include "Matrix4f.h"


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
			result[_row * 4 + _col] = 
		}
	}
	return Matrix4f();

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
Matrix4f operator*(float lhs, const Matrix4f & rhs)
{
	return rhs * lhs;
}
