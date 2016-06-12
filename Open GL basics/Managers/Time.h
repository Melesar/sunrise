#pragma once
#include <SDL/SDL_hints.h>

class Time
{
public:
	virtual ~Time();

	static float delta();
	static float time();

private:
	static Time* instance;

	static void Start();
	static void Update();

	Uint32 lastTick;

	Time();

	friend class Application;
};