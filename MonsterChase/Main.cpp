#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#endif // _DEBUG

#include "Engine.h"
#include "Game.h"

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{

	if (Engine::Startup(i_hInstance, i_hPrevInstance, i_lpCmdLine, i_nCmdShow))
	{
		if (Game::Startup())
		{
			Game::Run();
			Game::Shutdown();
		}
		Engine::Shutdown();
	}

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}