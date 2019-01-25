#include "RandomController.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>


RandomController::RandomController()
{
	m_Actor = nullptr;
}


void RandomController::UpdateActor()
{
	Point2D<float> move = GetRandomMovement();
	m_Actor->SetPosition(m_Actor->GetPosition() + move);
	std::cout << "Actor " << m_Actor->GetName() << " moves randomly to [" << m_Actor->GetPosition().getX() << ", " << m_Actor->GetPosition().getY() << "].\n";
}

Point2D<float> RandomController::GetRandomMovement()
{
	srand(time(NULL));
	return Point2D<float>(rand() % 3 - 1, rand() % 3 - 1);
}

RandomController::~RandomController()
{
}
