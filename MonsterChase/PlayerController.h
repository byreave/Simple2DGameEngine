#pragma once
#include "BaseController.h"
#include "Point2D.h"
class PlayerController :
	public BaseController
{
public:
	void SetActor(Actor * i_pActor) override { m_Actor = i_pActor; }
	void UpdateActor() override
	{
		if (m_Actor)
		{
			Point2D<int> Movement = GetMoveFromUserInput();
			m_Actor->SetPosition(m_Actor->GetPosition() + Movement);
		}
	}

	Point2D<int> GetMoveFromUserInput();
	void SetMove(char move) { m_move = move; }
	
private:
	Actor * m_Actor;
	char m_move;
};

