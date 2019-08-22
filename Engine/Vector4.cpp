#include "Vector4.h"
#include "Matrix4f.h"
#include "ConsoleLog.h"

Vector4 Vector4::operator * (const Matrix4f & rhs)
{
	/*return Vector4(
		_x * rhs(0, 0) + _y * rhs(1, 0) + _z * rhs(2, 0) + _w * rhs(3, 0),
		_x * rhs(0, 1) + _y * rhs(1, 1) + _z * rhs(2, 1) + _w * rhs(3, 1),
		_x * rhs(0, 2) + _y * rhs(1, 2) + _z * rhs(2, 2) + _w * rhs(3, 2),
		_x * rhs (0, 3) + _y * rhs(1, 3) + _z * rhs(2, 3) + _w * rhs(3, 3)
		);*/
	__m128 result = _mm_mul_ps(rhs.Rows(0), _mm_set1_ps(_x));
	result = _mm_add_ps(result, _mm_mul_ps(rhs.Rows(1), _mm_set1_ps(_y)));
	result = _mm_add_ps(result, _mm_mul_ps(rhs.Rows(2), _mm_set1_ps(_z)));
	result = _mm_add_ps(result, _mm_mul_ps(rhs.Rows(3), _mm_set1_ps(_w)));
	return Vector4(
		result
	);
}

void Vector4::Show()
{
	DEBUG_PRINT("Vector4 Info", "\n[%f, %f, %f, %f]", _x, _y, _z, _w);
}

float Vector4::Dot(const __m128 & rhs)
{
	// or _mm_dp_ps
	__m128 r1 = _mm_mul_ps(m_vec, rhs);
	__m128 shuf = _mm_shuffle_ps(r1, r1, _MM_SHUFFLE(2, 3, 0, 1));
	__m128 sums = _mm_add_ps(r1, shuf);
	shuf = _mm_movehl_ps(shuf, sums);
	sums = _mm_add_ss(sums, shuf);
	return _mm_cvtss_f32(sums);
}
