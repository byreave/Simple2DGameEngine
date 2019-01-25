#pragma once
#include <chrono>
#include <GLib.h>
namespace Game 
{
	void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
	bool Startup(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow);
	void Run();
	void Shutdown();

}