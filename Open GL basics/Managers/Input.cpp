#include "Input.h"

Input* Input::instance;

Input::~Input()
{
}

void Input::Start()
{
	if (instance != nullptr) {
		return;
	}

	instance = new Input();
}

void Input::Update()
{
	instance->ResetKeys();
	instance->ResetMouseButtons();

	SDL_Event e;
	if (SDL_PollEvent(&e)) {
		instance->HandleKeyboardInput(e);
		instance->HandleMouseInput(e);
	}
}

void Input::HandleKeyboardInput(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN) {
		keysPressed[mapping[e.key.keysym.sym]] = true;
		keysHold[mapping[e.key.keysym.sym]] = true;
	} else if (e.type == SDL_KEYUP) {
		keysHold[mapping[e.key.keysym.sym]] = false;
		keysReleased[mapping[e.key.keysym.sym]] = true;
	}
}

void Input::HandleMouseInput(SDL_Event& e)
{
	if (e.type != SDL_MOUSEBUTTONDOWN && e.type != SDL_MOUSEBUTTONUP) {
		return;
	}

	MouseButton button;
	switch (e.button.button) {
		case SDL_BUTTON_LEFT:
			button = Left;
			break;
		case SDL_BUTTON_RIGHT:
			button = Right;
			break;
		case SDL_BUTTON_MIDDLE:
			button = Middle;
			break;
	}

	if (e.type == SDL_MOUSEBUTTONDOWN) {
		mouseButtonsPressed[button] = true;
		mouseButtonsHold[button] = true;
	} else if (e.type == SDL_MOUSEBUTTONUP) {
		mouseButtonsReleased[button] = true;
		mouseButtonsHold[button] = false;
	}
}

void Input::ResetKeys()
{
	for (int i = 0; i < KEYS_AMOUNT; ++i) {
		keysReleased[i] = false;
		keysPressed[i] = false;
	}
}

void Input::ResetMouseButtons()
{
	for (int i = 0; i < BUTTONS_AMOUNT; ++i) {
		mouseButtonsPressed[i] = false;
		mouseButtonsReleased[i] = false;
	}
}

void Input::InitMapping()
{
	mapping[SDLK_w] = W;
	mapping[SDLK_a] = A;
	mapping[SDLK_s] = S;
	mapping[SDLK_d] = D;

	mapping[SDLK_f] = F;
	mapping[SDLK_q] = Q;
	mapping[SDLK_e] = E;
	mapping[SDLK_r] = R;
	mapping[SDLK_z] = Z;
	mapping[SDLK_x] = X;
	mapping[SDLK_c] = C;

	mapping[SDLK_SPACE] = Space;
	mapping[SDLK_RETURN] = Return;
	mapping[SDLK_BACKSPACE] = Backspace;
	mapping[SDLK_LALT] = LAlt;
	mapping[SDLK_LCTRL] = LCtrl;
	mapping[SDLK_LSHIFT] = LShift;
}

void Input::InitHoldings()
{
	for (int i = 0; i < KEYS_AMOUNT; ++i) {
		keysHold[i] = false;
	}

	for (int i = 0; i < BUTTONS_AMOUNT; ++i) {
		mouseButtonsHold[i] = false;
	}
}

Input::Input()
{
	InitMapping();
	InitHoldings();

	ResetKeys();
	ResetMouseButtons();
}