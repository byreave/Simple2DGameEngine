#include "Monster.h"
#include <iostream>
#include <math.h> //abs()
Monster::Monster()
{
	Name = NULL;
}

Monster::Monster(char * name, Position pos, int lives = 20)
{
	Name = new char[strlen(name)];
	memcpy(Name, name, strlen(name));
	Pos = pos;
	Lives = lives;
}

Monster::~Monster()
{
	if (Name != NULL)
		delete Name;
}


//True means that player was caught
bool Monster::Move(Position & playerPos, int & monCount, char * monName)
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

void Monster::respawn(char * monName, int & monCount)
{
	srand(monCount);
	int tmpCount = monCount;
	if (NULL != Name)
		delete Name;
	Name = new char[strlen(monName) + 2 + monCount / 26]; //Name after xxxA, xxxB ... xxxZ, xxxAA
	for (int i = 0; i < strlen(monName); ++i)
	{
		Name[i] = monName[i];
	}
	for (int i = 0; i < 1 + monCount / 26; ++i)
	{
		if(tmpCount / 26 == 0)
			Name[i + strlen(monName)] = 'A' + tmpCount % 26;
		else
		{
			Name[i + strlen(monName)] = 'A' + monCount / 26 - 1;
			tmpCount -= 26;
		}
	}
	Name[strlen(monName) + 1 + monCount / 26] = '\0';
	monCount++;
	Pos.x = rand() % 40 + 50;
	Pos.y = rand() % 101;
	Lives = 20;
}

