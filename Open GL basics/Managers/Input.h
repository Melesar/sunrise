#pragma once

#include "SDL/SDL.h"

class Input
{
public:
	virtual ~Input();
	
	enum KeyCode
	{
		W, A, S, D,
		F, R, E, Q, C, Z, X,
		Space,
		Return,
		Backspace,
		LShift,
		LCtrl,
		LAlt,

		KEYS_AMOUNT
	};

	enum MouseButton
	{
		Left, Right, Middle,

		BUTTONS_AMOUNT
	};

	static bool KeyPressed(KeyCode key) { return instance->keysPressed[key]; }
	static bool KeyHold(KeyCode key) { return instance->keysHold[key]; }
	static bool KeyReleased(KeyCode key) { return instance->keysReleased[key]; }

	static bool MouseButtonPressed(MouseButton button) { return instance->mouseButtonsPressed[button]; }
	static bool MouseButtonHold(MouseButton button) { return instance->mouseButtonsHold[button]; }
	static bool MouseButtonReleased(MouseButton button) { return instance->mouseButtonsReleased[button]; }

private :
	static Input* instance;

	static void Start();
	static void Update();

	//Mapping between SDL key codes and custom ones
	unsigned int mapping[323];

	bool keysPressed[KEYS_AMOUNT];
	bool keysHold[KEYS_AMOUNT];
	bool keysReleased[KEYS_AMOUNT];

	bool mouseButtonsPressed[BUTTONS_AMOUNT];
	bool mouseButtonsHold[BUTTONS_AMOUNT];
	bool mouseButtonsReleased[BUTTONS_AMOUNT];

	void PeekInputEvents();
	void HandleKeyboardInput(SDL_Event* events, int count);
	void HandleMouseInput(SDL_Event* events, int count);

	void ResetKeys();
	void ResetMouseButtons();

	void InitMapping();
	void InitHoldings();

	Input();

	friend class Application;
};
