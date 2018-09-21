#include "Monster.h"
#include <iostream>
#include <math.h> //abs()
Monster::Monster()
{
	Name = NULL;
}

Monster::Monster(char * name, Point2D<int> pos, int lives = 20)
{
	Name = new char[strlen(name)+1];
	memcpy(Name, name, strlen(name)+1);
	Pos = pos;
	Lives = lives;
}

Monster::~Monster()
{
	if (Name != NULL)
		delete Name;
}


//True means that player was caught
bool Monster::Move(Point2D<int> & playerPos, int & monCount, char * monName)
{
	int distanceX = playerPos.getX() - Pos.getX();
	int distanceY = playerPos.getY() - Pos.getY();

	
	if (abs(distanceX) >= abs(distanceY))
	{
		if (distanceX < 0)
			Pos.setX(Pos.getX() - 1);
		else
			Pos.setX(Pos.getX() + 1);

	}
	else
	{
		if (distanceY < 0)
			Pos.setY(Pos.getY() - 1);
		else
			Pos.setY(Pos.getY() + 1);
	}
	std::cout << "To approach player, Monster named " << Name << " moves to [" << Pos.getX() << ", " << Pos.getY() << "].\n";

	if (playerPos == Pos)
	{
		std::cout << "Monster named " << Name << "catches player at [" << Pos.getX() << ", " << Pos.getY() << "].\n" <<
			"However player fights valiantly and kills it, player HP - 1.\n";

		respawn(monName, monCount);

		std::cout << "To avenge its friend another monster named " << Name << " appears at [" << Pos.getX() << ", " << Pos.getY() << "].\n";
		return true;
	}

	if (--Lives <= 0)
	{
		std::cout << "After 20 moves and " << Name << " exhausted and died.\n";
		respawn(monName, monCount);
		std::cout << "In the meanwhile a monster named " << Name << " appears at [" << Pos.getX() << ", " << Pos.getY() << "].\n";
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
	for (unsigned int i = 0; i < strlen(monName); ++i)
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
	Pos.setX(rand() % 40 + 50);
	Pos.setY(rand() % 101);
	Lives = 20;
}

