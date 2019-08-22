#pragma once
#include <chrono>
#include <GLib.h>
namespace Game 
{
	extern bool bQuit;
	bool Startup();
	void Run();
	void Shutdown();
	void GameOver();
}