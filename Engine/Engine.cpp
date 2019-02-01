#include "Engine.h"
#include "GLib.h"
bool Engine::Startup(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	// IMPORTANT: first we need to initialize GLib
	return GLib::Initialize(i_hInstance, i_nCmdShow, "GLibTest", -1, 800, 600);
}

void Engine::Shutdown()
{
	// IMPORTANT:  Tell GLib to shutdown, releasing resources.
	GLib::Shutdown();
}
