#pragma once

#include "glm/glm.hpp"
#include "../Component model/Component.h"
#include "../Data/Structs.h"

#include <SDL/SDL.h>
#include <string>

typedef SDL_Rect Rect;

struct Color;

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();

	glm::mat4 GetViewProjection() const;
	Rect cameraRect() const;

	void EnableBackCulling(bool enable);
	void EnableZBuffer(bool enable);

	void Init() override;
	void Update() override;

	bool IsBackCulling() { return backCullingEnabled; }
	bool IsZBufferEnabled() { return zBufferEnabled; }

	glm::vec3 ScreenToWorldCoordinates(const glm::vec2 screenCoords) const;

	static Camera* mainCamera;
private:
	static SDL_Window*    window;
	static SDL_GLContext  context;
	static SDL_Surface*   windowSurface;

	static int camerasActive;
	static bool windowInitialized;

	SDL_Surface* cameraSurface;

	Color backgroundColor;
	Transform* transform;

	glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 forwardDirection;
	glm::vec3 upDirection;

	float fov;
	float aspect;
	float zNear;
	float zFar;

	bool zBufferEnabled = true;
	bool backCullingEnabled = true;

	std::string title;

	void InitWindow();
	void Clear();
	void UpdateDirections();
};

