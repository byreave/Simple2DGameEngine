#include "ConsoleLog.h"
#include <assert.h>
#include <Windows.h>
#include "Game.h"
#include "Clock.h"
#include <vector>
#include "Renderable.h"
#include "PhysicsSystem.h"
#include "LuaCreateGO.h"
#include "MatrixVector4Unittest.h"

std::vector<StrongPointer<GameObject>> AllGameObjects;
std::vector<Physics::PhysicsSystem *> Physics::PhysicsInfo;
std::vector<Render::Renderable *> Render::RenderableInfo;

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
	if (i_VKeyID == 'a' || i_VKeyID == 'A')
	{
		if (bWentDown)
		{
			DEBUG_PRINT("Info", "A pressed!");
			for (auto phy = Physics::PhysicsInfo.begin(); phy != Physics::PhysicsInfo.end(); ++phy)
			{
				Physics::PhysicsSystem * p = *phy;
				p->AddForce(-100.0f, 0.0f);
			}
		}
		else
		{
			for (auto phy = Physics::PhysicsInfo.begin(); phy != Physics::PhysicsInfo.end(); ++phy)
			{
				Physics::PhysicsSystem * p = *phy;
				p->AddForce(100.0f, 0.0f);
			}
		}

	}
	else if (i_VKeyID == 'd' || i_VKeyID == 'D')
	{
		if (bWentDown)
		{
			DEBUG_PRINT("Info", "D pressed!");
			for (auto phy = Physics::PhysicsInfo.begin(); phy != Physics::PhysicsInfo.end(); ++phy)
			{
				Physics::PhysicsSystem * p = *phy;
				p->AddForce(100.0f, 0.0f);
			}
		}
		else
		{
			for (auto phy = Physics::PhysicsInfo.begin(); phy != Physics::PhysicsInfo.end(); ++phy)
			{
				Physics::PhysicsSystem * p = *phy;
				p->AddForce(-100.0f, 0.0f);
			}
		}
	}
#ifdef _DEBUG
	/*const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);*/
#endif // __DEBUG
}

bool Game::Startup()
{
	Unittest_Matrix_Vector();
	Engine::CreateGO("data\\player.lua");
	// IMPORTANT (if we want keypress info from GLib): Set a callback for notification of key presses
	GLib::SetKeyStateChangeCallback(TestKeyCallback);
	Timing::deltaTime = Timing::Clock::now();

	return true;
}

void Game::Run()
{
	bool bQuit = false;

	do
	{
		// IMPORTANT: We need to let GLib do it's thing.
		GLib::Service(bQuit);

		if (!bQuit)
		{
			float deltaTime = Timing::GetTimeSinceLastCall() / 1000.0f;
			//DEBUG_PRINT("Time: ", "Time Since Last Call : %f", Timing::GetTimeSinceLastCall());
			Physics::Update(deltaTime);
			//DEBUG_PRINT("Debug", "Character x pos: %f", (*AllGameObjects.begin())->GetPosition().getX());
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
	Physics::CleanUp();
	Render::CleanUp();
	AllGameObjects.clear();
	AllGameObjects.~vector();
}
