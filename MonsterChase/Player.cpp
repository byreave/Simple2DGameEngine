#include "Player.h"
#include <iostream>




Player::Player(const Point2D<int> & pos, int lives)
{
	Pos = pos;
	Lives = lives;
}

Player::Player(char * name)
{
	Name = new char[strlen(name) + 1];
	memcpy(Name, name, strlen(name) + 1);
	Lives = 3;
}

Player::~Player()
{
	if (Name != nullptr)
		delete Name;
}

void Player::Move(char direction)
{
	if(direction == 'W' || direction == 'w')
		if (Pos.getY() > 0)
		{
			Pos.setY(Pos.getY() - 1);
			std::cout << "Player "<< Name << " moves up to [" << Pos.getX() << ", " << Pos.getY() << "].\n";
		}
		else
		{
			std::cout << "Player " << Name << " fails to move up and remains at [" << Pos.getX() << ", " << Pos.getY() << "].\n";
		}
	else if (direction == 'A' || direction == 'a')
		if (Pos.getX() > 0)
		{
			Pos.setX(Pos.getX() - 1);
			std::cout << "Player " << Name << " moves left to [" << Pos.getX() << ", " << Pos.getY() << "].\n";
		}
		else
		{
			std::cout << "Player " << Name << " fails to move left and remains at [" << Pos.getX() << ", " << Pos.getY() << "].\n";
		}
	else if (direction == 'S' || direction == 's')
		if (Pos.getY() < 101)
		{
			Pos.setY(Pos.getY() + 1);
			std::cout << "Player " << Name << " moves down to [" << Pos.getX() << ", " << Pos.getY() << "].\n";
		}
		else
		{
			std::cout << "Player " << Name << " fails to move down and remains at [" << Pos.getX() << ", " << Pos.getY() << "].\n";
		}
	else if (direction == 'D' || direction == 'd')
		if (Pos.getX() < 101)
		{
			Pos.setX(Pos.getX() + 1);
			std::cout << "Player " << Name << " moves right to [" << Pos.getX() << ", " << Pos.getY() << "].\n";
		}
		else
		{
			std::cout << "Player " << Name << " fails to move right and remains at [" << Pos.getX() << ", " << Pos.getY() << "].\n";
		}
	else
	{
		//do noting
	}
}
