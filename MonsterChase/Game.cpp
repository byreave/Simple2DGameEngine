#include "ConsoleLog.h"
#include <assert.h>
#include <Windows.h>
#include "Game.h"
#include "Clock.h"
#include <vector>
#include "Renderable.h"
#include "PhysicsSystem.h"
#include "LuaCreateGO.h"
#include "Collision.h"
#include "MatrixVector4Unittest.h"
#include "PlatformController.h"
#include "RandomMoveController.h"
#include "Engine.h"

bool Game::bQuit = false;

bool Game::Startup()
{
	//Unittest_Matrix_Vector();
	//CollisionSystem::Collision_UnitTest();
	Engine::RegisterController("platform", &Engine::Controller::PlatformController::PlatformControllerFactory);
	Engine::RegisterController("randommove", &Engine::Controller::RandomMoveController::RandomMoveControllerFactory);
	Engine::CreateGO("data\\player.lua");
	Engine::CreateGO("data\\enemy.lua");
	Engine::CreateGO("data\\LeftWall.lua");
	Engine::CreateGO("data\\RightWall.lua");
	Engine::CreateGO("data\\Ceiling.lua");
	//GLib::SetKeyStateChangeCallback(TestKeyCallback);

	return true;
}

void Game::Run()
{
	using namespace Engine;
	Timing::deltaTime = Timing::Clock::now();

	do
	{
		float deltaTime = Timing::GetTimeSinceLastCall();
		if (deltaTime > 2.0f)
			deltaTime = 0.5f;
		// IMPORTANT: We need to let GLib do it's thing.
		GLib::Service(bQuit);

		if (!bQuit)
		{
			//deltaTime = 16.667f;
			//ConsoleLog("asdasd", "%f", deltaTime);
			//Collision
			CollisionSystem::Update(deltaTime);
			//Physics
			Physics::Update(deltaTime);
			//
			Controller::Update();
			// IMPORTANT: Tell GLib that we want to start rendering
			GLib::BeginRendering();
			// Tell GLib that we want to render some sprites
			GLib::Sprites::BeginRendering();
			Render::RenderAll();
			// Tell GLib we're done rendering sprites
			GLib::Sprites::EndRendering();
			// IMPORTANT: Tell GLib we're done rendering
			GLib::EndRendering();
		}
	} while (bQuit == false);
}

void Game::Shutdown()
{
	using namespace Engine;
	Physics::CleanUp();
	Render::CleanUp();
	CollisionSystem::CleanUp();
	AllGameObjects.clear();
	AllGameObjects.~vector();
	Controller::CleanUp();
	Input::Release();
	ControllerMapping->clear();
	delete ControllerMapping;
	//ControllerMapping.~map();
}

void Game::GameOver()
{
	bQuit = true;
}
