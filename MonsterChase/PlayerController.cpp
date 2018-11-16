#include "PlayerController.h"




Point2D<int> PlayerController::GetMoveFromUserInput()
{
	switch (m_move)
	{
	case 'w':
	case 'W':
		return Point2D<int>(0, -1);
		break;
	case 'a':
	case 'A':
		return Point2D<int>(-1, 0);
		break;
	case 's':
	case 'S':
		return Point2D<int>(0, 1);
		break;
	case 'd':
	case 'D':
		return Point2D<int>(1, 0);
		break;
	default:
		break;
	}
}
