#include "Application.h"
#include <SDL/SDL.h>

Application* Application::instance;

void Application::Start()
{
	if (instance != nullptr) {
		return;
	}

	instance = new Application();
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
}

Application::Application()
{
	isActive = true;
}

void Application::HandleEvent()
{
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		isActive = e.type != SDL_QUIT;
	}
}