#include "Player.h"
#include <iostream>




Player::Player(Position pos, int lives)
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
}

void Player::Move(char direction)
{
	if(direction == 'W' || direction == 'w')
		if (Pos.y > 0)
		{
			Pos.y--;
			std::cout << "Player "<< Name << " moves up to [" << Pos.x << ", " << Pos.y << "].\n";
		}
		else
		{
			std::cout << "Player " << Name << " fails to move up and remains at [" << Pos.x << ", " << Pos.y << "].\n";
		}
	else if (direction == 'A' || direction == 'a')
		if (Pos.x > 0)
		{
			Pos.x--;
			std::cout << "Player " << Name << " moves left to [" << Pos.x << ", " << Pos.y << "].\n";
		}
		else
		{
			std::cout << "Player " << Name << " fails to move left and remains at [" << Pos.x << ", " << Pos.y << "].\n";
		}
	else if (direction == 'S' || direction == 's')
		if (Pos.y < 101)
		{
			Pos.y++;
			std::cout << "Player " << Name << " moves down to [" << Pos.x << ", " << Pos.y << "].\n";
		}
		else
		{
			std::cout << "Player " << Name << " fails to move down and remains at [" << Pos.x << ", " << Pos.y << "].\n";
		}
	else if (direction == 'D' || direction == 'd')
		if (Pos.x < 101)
		{
			Pos.x++;
			std::cout << "Player " << Name << " moves right to [" << Pos.x << ", " << Pos.y << "].\n";
		}
		else
		{
			std::cout << "Player " << Name << " fails to move right and remains at [" << Pos.x << ", " << Pos.y << "].\n";
		}
	else
	{
		//do noting
	}
}
