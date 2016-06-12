#include "Time.h"
#include "SDL/SDL.h"

Time* Time::instance;

Time::~Time()
{
	
}

Time::Time()
{
	lastTick = SDL_GetTicks();
}

void Time::Start()
{
	if (instance != nullptr) {
		return;
	}

	instance = new Time();
}

void Time::Update()
{
	instance->lastTick = SDL_GetTicks();
}

float Time::delta()
{
	return static_cast<float>(SDL_GetTicks() - instance->lastTick) / 1000.0f;
}

float Time::time()
{
	return static_cast<float>(SDL_GetTicks()) / 1000.0f;
}
