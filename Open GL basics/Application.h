#pragma once

class Application
{
public:

	static void Start();
	static bool IsActive();
	static void Update();

private:
	static Application* instance;
	Application();

	void HandleEvent();

	bool isActive;
};
