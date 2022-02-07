#include "Timer.h"

void Timer::startTimer()
{
	start = system_clock::now();
}

void Timer::stopTimer()
{
	stop = system_clock::now();
}

int64_t Timer::getTimeWithoutStopping()
{
	return duration_cast<seconds>(system_clock::now() - start).count();
}

int64_t Timer::getTimeMSWithoutStopping()
{
	return duration_cast<milliseconds>(system_clock::now() - start).count();
}