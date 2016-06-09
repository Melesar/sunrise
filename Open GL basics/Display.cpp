#include "Display.h"
#include <GL/glew.h>
#include <iostream>


Display::Display(int width, int height, const std::string& title)
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
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

	//GL контекст передает контроль над окном видеокарте, вместо операционной системе. Необходимо для рисования
	glContext = SDL_GL_CreateContext(window);

	//Ищет все поддерживаемые системой функции OpenGL и инициализирует их
	GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		std::cerr << "GLEW failed to initialize" << std::endl;
	}

	isClosed = false;

	//Включаем куллинг задних поверхностей - поверхность модели, направленная в другую сторону от камеры,
	//не будет отрисовываться
	//Работает корректно только для выпуклых моделей
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	//Включаем z-буффер
	glEnable(GL_DEPTH_TEST);
}

Display::~Display()
{
	//Очистка контекста и уничтожение окна. Порядок вызова имеет значение!
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);

	//Выход из SDL
	SDL_Quit();
}

void Display::Clear(float r, float g, float b, float a)
{
	//Устанавливает цвет в буффер цвета
	glClearColor(r, g, b, a);

	//Заполняет окно установленным цветом
	//GL_DEPTH_BUFFER_BIT очищает z-буффер, что бы на следующем кадре снова сортировать все заново
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Display::IsClosed()
{
	return isClosed;
}

//Применение двойной буферизации, объявленной в конструкторе
//Переключает окно на блок памяти, в котором OpenGL совершила отрисовку. OpenGL при этом переходит на освободившийся блок памяти.
//Позволяет избежать графических артефактов, когда в окне отображается не до конца отрисованный контент
//Визуализация здесь: https://youtu.be/DkiKgQRiMRU?t=16m19s
void Display::SwapBuffers()
{
	SDL_GL_SwapWindow(window);
}

void Display::Update()
{
	SwapBuffers();

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			isClosed = true;
		}
	}
}