#pragma once

#include <time.h>//time()


struct Position
{
	int x;
	int y;

	bool operator ==(Position other)
	{
		if (x == other.x && y == other.y)
			return true;
		else
			return false;
	}
};