#include "Application.h"
#include "Time.h"
#include "Input.h"
#include <SDL/SDL.h>

Application* Application::instance;

void Application::Start()
{
	if (instance != nullptr) {
		return;
	}

	instance = new Application();

	Time::Start();
	Input::Start();
}

bool Application::IsActive()
{
	return instance != nullptr && instance->isActive;
}

void Application::Update()
{
	if (instance == nullptr) {
		return;
	}

	instance->HandleEvent();

	Time::Update();
	Input::Update();
}

Application::Application()
{
	isActive = true;
}

void Application::HandleEvent()
{
	SDL_Event e[1];
	
	int count =  SDL_PeepEvents(e, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT);
	isActive = count == 0;
	/*if (SDL_PollEvent(&e))
	{
		isActive = e.type != SDL_QUIT;
	}*/
}