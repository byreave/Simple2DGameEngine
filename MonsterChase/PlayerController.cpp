#include "PlayerController.h"
#include<iostream>



void PlayerController::UpdateActor()
{
	{
		if (m_Actor)
		{
			Point2D<float> Movement = GetMoveFromUserInput();
			if (m_move == 'W' || m_move == 'w')
				if (m_Actor->GetPosition().getY() > 0)
				{
					m_Actor->SetPosition(m_Actor->GetPosition() + Movement);
					std::cout << "Player " << m_Actor->GetName() << " moves up to [" << m_Actor->GetPosition().getX() << ", " << m_Actor->GetPosition().getY() << "].\n";
				}
				else
				{
					std::cout << "Player " << m_Actor->GetName() << " fails to move up and remains at [" << m_Actor->GetPosition().getX() << ", " << m_Actor->GetPosition().getY() << "].\n";
				}
			else if (m_move == 'A' || m_move == 'a')
				if (m_Actor->GetPosition().getX() > 0)
				{
					m_Actor->SetPosition(m_Actor->GetPosition() + Movement);
					std::cout << "Player " << m_Actor->GetName() << " moves left to [" << m_Actor->GetPosition().getX() << ", " << m_Actor->GetPosition().getY() << "].\n";
				}
				else
				{
					std::cout << "Player " << m_Actor->GetName() << " fails to move left and remains at [" << m_Actor->GetPosition().getX() << ", " << m_Actor->GetPosition().getY() << "].\n";
				}
			else if (m_move == 'S' || m_move == 's')
				if (m_Actor->GetPosition().getY() < 101)
				{
					m_Actor->SetPosition(m_Actor->GetPosition() + Movement);
					std::cout << "Player " << m_Actor->GetName() << " moves down to [" << m_Actor->GetPosition().getX() << ", " << m_Actor->GetPosition().getY() << "].\n";
				}
				else
				{
					std::cout << "Player " << m_Actor->GetName() << " fails to move down and remains at [" << m_Actor->GetPosition().getX() << ", " << m_Actor->GetPosition().getY() << "].\n";
				}
			else if (m_move == 'D' || m_move == 'd')
				if (m_Actor->GetPosition().getX() < 101)
				{
					m_Actor->SetPosition(m_Actor->GetPosition() + Movement);
					std::cout << "Player " << m_Actor->GetName() << " moves right to [" << m_Actor->GetPosition().getX() << ", " << m_Actor->GetPosition().getY() << "].\n";
				}
				else
				{
					std::cout << "Player " << m_Actor->GetName() << " fails to move right and remains at [" << m_Actor->GetPosition().getX() << ", " << m_Actor->GetPosition().getY() << "].\n";
				}
			else
			{
				//do noting
			}
		}
	}
}

Point2D<float> PlayerController::GetMoveFromUserInput()
{
	switch (m_move)
	{
	case 'w':
	case 'W':
		return Point2D<float>(0, -1);
		break;
	case 'a':
	case 'A':
		return Point2D<float>(-1, 0);
		break;
	case 's':
	case 'S':
		return Point2D<float>(0, 1);
		break;
	case 'd':
	case 'D':
		return Point2D<float>(1, 0);
		break;
	default:
		return Point2D<float>(0, 0);
		break;
	}
}

PlayerController::~PlayerController()
{
}
