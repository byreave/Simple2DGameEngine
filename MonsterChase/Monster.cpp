#include "Monster.h"
#include <iostream>
#include <math.h>
Monster::Monster()
{
}

Monster::Monster(string name, Position pos, int lives = 20)
{
	Name = name;
	Pos = pos;
	Lives = lives;
}

Monster::~Monster()
{
}


//True means that player was caught
bool Monster::Move(Position & playerPos, int & monCount, string monName)
{
	int distanceX = playerPos.x - Pos.x;
	int distanceY = playerPos.y - Pos.y;

	
	if (abs(distanceX) >= abs(distanceY))
	{
		if (distanceX < 0)
			Pos.x--;
		else
			Pos.x++;
	}
	else
	{
		if (distanceY < 0)
			Pos.y--;
		else
			Pos.y++;
	}
	std::cout << "To approach player, Monster named " << Name << " moves to [" << Pos.x << ", " << Pos.y << "].\n";

	if (playerPos == Pos)
	{
		std::cout << "Monster named " << Name << "catches player at [" << Pos.x << ", " << Pos.y << "].\n" <<
			"However player fights valiantly and kills it, player HP - 1.\n";

		respawn(monName, monCount);

		std::cout << "To avenge its friend another monster named " << Name << " appears at [" << Pos.x << ", " << Pos.y << "].\n";
		return true;
	}

	if (--Lives <= 0)
	{
		std::cout << "After 20 moves and " << Name << " exhausted and died.\n";
		respawn(monName, monCount);
		std::cout << "In the meanwhile a monster named " << Name << " appears at [" << Pos.x << ", " << Pos.y << "].\n";
	}

	return false;
}

void Monster::respawn(string monName, int & monCount)
{
	srand(monCount);

	Name = monName + to_string(monCount++);
	Pos.x = rand() % 40 + 50;
	Pos.y = rand() % 101;
	Lives = 20;
}

