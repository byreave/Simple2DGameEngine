#include "Monster.h"

Monster::Monster()
{
}

Monster::Monster(string name, Position pos, int lives = 1)
{
	Name = name;
	Pos = pos;
	Lives = lives;
}


Monster::~Monster()
{
}

void Monster::Move(Position playerPos)
{
}
