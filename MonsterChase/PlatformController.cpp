#include "PlatformController.h"

void Engine::Controller::PlatformController::HandleButtonMovement(unsigned int i_Vkey, bool b_WentDown)
{
	if (i_Vkey == 'A' || i_Vkey == 'a')
	{
		if (b_WentDown)
		{
			auto spGO = gameObject.AcquireOwnership();
			spGO->SetVelocity(spGO->GetVelocity() - MoveSpeed);
		}
		else
		{
			auto spGO = gameObject.AcquireOwnership();
			spGO->SetVelocity(spGO->GetVelocity() + MoveSpeed);
		}
	}

	if (i_Vkey == 'D' || i_Vkey == 'd')
	{
		if (b_WentDown)
		{
			auto spGO = gameObject.AcquireOwnership();
			spGO->SetVelocity(spGO->GetVelocity() + MoveSpeed);
		}
		else
		{
			auto spGO = gameObject.AcquireOwnership();
			spGO->SetVelocity(spGO->GetVelocity() - MoveSpeed);
		}
	}
}

void Engine::Controller::PlatformController::PlatformControllerFactory(Engine::StrongPointer<GameObject> i_GameObject)
{
	Controller::Controllers.push_back(new PlatformController(i_GameObject, Point2D<float>(2.0f, 0.0f)));
}
