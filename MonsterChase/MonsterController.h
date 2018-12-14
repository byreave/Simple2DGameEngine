#pragma once
#include "BaseController.h"
class MonsterController :
	public BaseController
{
public:
	MonsterController()
	{
		MonsterController::MonsterID++;
		m_Actor = nullptr;
		m_Target = nullptr;
	}
	~MonsterController();
	void SetActor(Actor * i_pActor) override { m_Actor = i_pActor; }
	void SetTarget(Actor * i_pTarget) { m_Target = i_pTarget; }
	void UpdateActor() override
	{
		if (m_Actor)
		{
			Move(m_Target->GetPosition());
		}
	}
	//Move Monster according to player's position:AI
	bool Move(const Point2D<int> & playerPos);
	bool Respawn();
	static void SetIDZero()
	{
		MonsterController::MonsterID = 0;
	}

private:
	Actor * m_Actor;
	Actor * m_Target;
	static int MonsterID;
};

