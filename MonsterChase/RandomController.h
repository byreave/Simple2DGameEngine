#pragma once
#include "BaseController.h"
class RandomController :
	public BaseController
{
public:
	RandomController();
	void SetActor(Actor * i_pActor) override { m_Actor = i_pActor; }
	void UpdateActor() override;
	Point2D<float> GetRandomMovement();
	~RandomController();
private:
	Actor * m_Actor;
};

