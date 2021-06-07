#pragma once
#include <chrono>

class FrameTimer
{
private:
	std::chrono::time_point<std::chrono::steady_clock> beforeFrame;

public:
	FrameTimer();
	float resetFrameTime();
};