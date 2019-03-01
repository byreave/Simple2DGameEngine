#pragma once
class BaseController
{
public:
	virtual void SetActor(Actor * i_pActor) = 0;
	virtual void UpdateActor() = 0;
};

