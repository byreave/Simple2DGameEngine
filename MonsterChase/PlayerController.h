#pragma once
#include "BaseController.h"
#include "Point2D.h"
class PlayerController :
	public BaseController
{
public:
	void SetActor(Actor * i_pActor) override { m_Actor = i_pActor; }
	void UpdateActor() override;
	

	Point2D<float> GetMoveFromUserInput();
	void SetMove(char move) { m_move = move; }
	~PlayerController();
	
private:
	Actor * m_Actor;
	char m_move;
};

