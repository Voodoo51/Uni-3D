#include "Timer.h"

Timer timer;

void Timer::Init(int capLimit)
{
	this->capLimit = capLimit;
	current = 0;
	previous = 0;
}

void Timer::Tick()
{
	current = SDL_GetTicks64();

	deltaTime = (current - previous);

	time += deltaTime;
}


bool Timer::CanUpdate()
{
	if (deltaTime > 1000.0 / capLimit)
	{	
		previous = current;
		return true;
	}
	else
	{
		return false;
	}
}