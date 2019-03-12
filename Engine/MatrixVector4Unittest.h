#pragma once
#include "Matrix4f.h"
#include "Vector4.h"
void Unittest_Matrix_Vector()
{
	Matrix4f testmatA(
		1.0f, 1.0f, 1.0f, 0.0f,
		2.0f, 3.0f, 2.0f, 1.0f,
		3.0f, 1.0f, 5.0f, 0.0f,
		0.0f, 2.0f, 4.0f, 1.0f
	);
	Matrix4f testmatB(
		1.0f, 3.0f, 1.0f, 0.0f,
		2.0f, 1.0f, 2.0f, 1.0f,
		3.0f, 1.0f, 4.0f, 3.0f,
		2.0f, 2.0f, 4.0f, 1.0f
	);

	Vector4 testvecA(1.0f, 2.0f, 3.0f, 4.0f);
	testmatA.Show();

	//add
	(testmatA + testmatB).Show();
	//substract
	(testmatA - testmatB).Show();
	//multiply
	(testmatA * testmatB).Show();
	(testmatA * 4).Show();
	(testmatA * testvecA).Show();
	(testvecA * testmatA).Show();
	//inverse
	testmatA.Inverse().Show();
	//transpose
	testmatA.Transpose().Show();
}