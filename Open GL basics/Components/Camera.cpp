#include "Camera.h"
#include "glm/gtx/transform.hpp"
#include <GL/glew.h>
#include "Transform.h"

SDL_Window*    Camera::window;
SDL_GLContext  Camera::context;
SDL_Surface*   Camera::windowSurface;
Camera*        Camera::mainCamera;

bool Camera::windowInitialized;
int Camera::camerasActive;

Camera::Camera() :
	backgroundColor  (0.0f, 0.15f, 0.3f, 1.0f),
	forwardDirection (glm::vec3(0, 0, 1)),
	upDirection		 (glm::vec3(0, 1, 0)), 
	fov				 (70.0f), 
	aspect			 (static_cast<float>(800) / 600),
	zNear			 (0.01f),
	zFar			 (1000.0f)
{
	
}

Camera::~Camera()
{
	if (--camerasActive == 0) {
		//Очистка контекста и уничтожение окна. Порядок вызова имеет значение!
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);

		//Выход из SDL
		SDL_Quit();
	}
}

glm::mat4 Camera::GetViewProjection() const
{
	auto pos = transform->position();
	return perspective * lookAt(pos, pos + forwardDirection, upDirection);
}

Rect Camera::cameraRect() const
{
	return cameraSurface->clip_rect;
}

void Camera::EnableBackCulling(bool enable)
{
	backCullingEnabled = enable;
    if (enable) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
    } else {
		glDisable(GL_CULL_FACE);
    }
}

void Camera::EnableZBuffer(bool enable)
{
	zBufferEnabled = enable;
	if (enable) {
		glEnable(GL_DEPTH_TEST);
	} else {
		glDisable(GL_DEPTH_TEST);
	}
}

void Camera::Init()
{
	perspective = glm::perspective(fov, aspect, zNear, zFar);
	transform = &GetComponent<Transform>();

	if (!windowInitialized) {
		InitWindow();
	}

	mainCamera = this;

	cameraSurface = SDL_GetWindowSurface(window);
	camerasActive++;
	
	EnableBackCulling(true);
	EnableZBuffer(true);
}

void Camera::Update()
{
	SDL_GL_SwapWindow(window);
	Clear();
}

void Camera::InitWindow()
{
	//Инициализация SDL и всех её компонентов
	SDL_Init(SDL_INIT_EVERYTHING);

	//Задание кол-ва бит для каждого цвета
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	//Общий размер буффера цвета (8 + 8 + 8 + 8 = 32)
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);

	//Выделяем память под z-буффер - способ корректной отрисовки невыпуклых моделей
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

	//Команда на выделение памяти для двух окон
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	//Создание окна SDL. Последний флаг означает, что оно будет использовано для отрисовки с помощью OpenGL
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	windowSurface = SDL_GetWindowSurface(window);

	//GL контекст передает контроль над окном видеокарте, вместо операционной системе. Необходимо для рисования
	context = SDL_GL_CreateContext(window);

	//Ищет все поддерживаемые системой функции OpenGL и инициализирует их
	glewInit();

	windowInitialized = true;
}

void Camera::Clear()
{
	//Устанавливает цвет в буффер цвета
	glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

	//Заполняет окно установленным цветом
	//GL_DEPTH_BUFFER_BIT очищает z-буффер, что бы на следующем кадре снова сортировать все заново
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}