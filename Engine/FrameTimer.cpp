#include "FrameTimer.h"

using namespace std::chrono;

FrameTimer::FrameTimer()
{
	beforeFrame = steady_clock::now();
}

float FrameTimer::resetFrameTime()
{
	const auto afterFrame = steady_clock::now();
	duration<float> secondsPerFrame = afterFrame - beforeFrame;
	beforeFrame = afterFrame;
	return secondsPerFrame.count();
}