#pragma once
#include "Matrix4f.h"
#include "Vector4.h"
void Unittest_Matrix_Vector()
{
	Matrix4f testmat;
	testmat = 4 * testmat;
	testmat = testmat * 4;
}