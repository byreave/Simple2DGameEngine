#include "Point2D.h"
#include <assert.h>
bool Point2D_UnitTest()
{
	using namespace Engine;
	const Point2D<int> constPntA(0, 0);
	Point2D<int> PntA(1, 1);
	int x = PntA.getX();
	int constx1 = constPntA.getX();
	const int constx2 = constPntA.getX();
	assert(constx1 = constx2);
	
	return false;
}