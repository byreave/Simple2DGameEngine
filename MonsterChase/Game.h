#pragma once
#include <chrono>
#include <GLib.h>
namespace Game 
{
	void * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
	GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
	bool Startup();
	void Run();
	void Shutdown();

}