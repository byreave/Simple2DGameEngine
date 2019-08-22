#include "BaseController.h"

void Engine::Controller::Update()
{
	for (auto con = Controllers.begin(); con != Controllers.end(); ++con)
	{
		(*con)->Update();
	}
}

void Engine::Controller::CleanUp()
{
	for (auto con = Controllers.begin(); con != Controllers.end(); ++con)
	{
		delete (*con);
	}
	Controllers.~vector();
}
