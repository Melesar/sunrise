#pragma once
#include <string>
#include <SDL/SDL.h>

class Display
{
public:
	Display(int width, int height, const std::string& title);
	virtual ~Display();

	void Clear(float r, float g, float b, float a);
	bool IsClosed();
	void Update();

private:
	SDL_Window* window;
	SDL_GLContext glContext;

	bool isClosed;

	void SwapBuffers();
};

