#pragma once
#include <iostream>
#include <chrono>

using namespace std::chrono;

class Timer
{
	system_clock::time_point start;
	system_clock::time_point stop;

public:
	void startTimer();
	void stopTimer();
	int64_t getTimeWithoutStopping();
	int64_t getTimeMSWithoutStopping();
};

