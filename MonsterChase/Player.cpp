#include "Player.h"
#include <iostream>




Player::Player(Position pos, int lives)
{
	Pos = pos;
	Lives = lives;
}

Player::Player()
{
	Lives = 3;
}

Player::~Player()
{
}

void Player::Move(char direction)
{
	switch (direction)
	{
	case 'W':
		if (Pos.y > 0)
		{
			Pos.y--;
			std::cout << "Player moves up to [" << Pos.x << ", " << Pos.y << "].\n";
		}
		else
		{
			std::cout << "Player fails to move up and remains at [" << Pos.x << ", " << Pos.y << "].\n";
		}
		break;
	case 'A':
		if (Pos.x > 0)
		{
			Pos.x--;
			std::cout << "Player moves left to [" << Pos.x << ", " << Pos.y << "].\n";
		}
		else
		{
			std::cout << "Player fails to move left and remains at [" << Pos.x << ", " << Pos.y << "].\n";
		}
		break;
	case 'S':
		if (Pos.y < 101)
		{
			Pos.y--;
			std::cout << "Player moves down to [" << Pos.x << ", " << Pos.y << "].\n";
		}
		else
		{
			std::cout << "Player fails to move down and remains at [" << Pos.x << ", " << Pos.y << "].\n";
		}
		break;
	case 'D':
		if (Pos.x < 101)
		{
			Pos.x--;
			std::cout << "Player moves right to [" << Pos.x << ", " << Pos.y << "].\n";
		}
		else
		{
			std::cout << "Player fails to move right and remains at [" << Pos.x << ", " << Pos.y << "].\n";
		}
		break;
	default:
		//do nothing
		break;
	}
}
