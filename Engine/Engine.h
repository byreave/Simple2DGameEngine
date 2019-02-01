#pragma once
#include <Windows.h>
namespace Engine {
	bool Startup(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow);
	
	void Shutdown();
}