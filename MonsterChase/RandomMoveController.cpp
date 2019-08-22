#include "RandomMoveController.h"

void Engine::Controller::RandomMoveController::RandomMoveControllerFactory(StrongPointer<GameObject> i_GameObject)
{
	Controller::Controllers.push_back(new RandomMoveController(i_GameObject));
}
