#pragma once
#include <chrono>
namespace Timing
{
	typedef std::chrono::high_resolution_clock Clock;
	static auto deltaTime = Timing::Clock::now();
	float GetTimeSinceLastCall();
}