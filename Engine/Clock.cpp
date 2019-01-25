#include "Clock.h"

float Timing::GetTimeSinceLastCall()
{
	auto nowTime = Clock::now();
	std::chrono::duration<float, std::milli> duration = nowTime - deltaTime;
	deltaTime = nowTime;
	return duration.count();
}
