#include "Display.h"
#include "Data/Shader.h"
#include "Components/Mesh.h"
#include "Components/Transform.h"
#include "Components/Camera.h"

#undef main
#include "Data/Texture.h"
#include "Component model/GameObject.h"

int main()
{
	Display display(800, 600, "Display");
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Texture potTexture("./res/pot.JPG");
	Transform transform;
	Camera camera (glm::vec3(0, 0, -7), 70.0f, static_cast<float>(800) / 600, 0.01f, 1000.0f);

	//Определяем массив вершин
	//Система координат OpenGL
	//       1
	//-1     0      1
	//      -1
	Vertex vertices[] = {
		Vertex {glm::vec3(-1, -1, 0), glm::vec2(0, 0) },
		Vertex {glm::vec3(1, -1, 0), glm::vec2(0, 1) },
		Vertex {glm::vec3(1, 1, 0), glm::vec2(1, 0) },
		Vertex {glm::vec3(-1, 1, 0), glm::vec2(1, 1) },

		Vertex {glm::vec3(-1, 1, 1), glm::vec2(0, 0) },
		Vertex {glm::vec3(1, 1, 1), glm::vec2(0, 1) },

		Vertex {glm::vec3(1, -1, 1), glm::vec2(0, 0) },
		Vertex {glm::vec3(-1, -1, 1), glm::vec2(0, 1) },
	};

	unsigned int indices[] = { 0, 1, 2,   0, 2, 3,   2, 5, 6,   2, 1, 6,   0, 7, 6,   0, 1, 6,   4, 7, 6,   4, 5, 6,    4, 7, 0,   4, 3, 0,   4, 5, 3,   3, 5, 2 };

	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	Mesh loadedMesh("./res/monkey3.obj");

	float counter = 0.0f;

	while(!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		transform.position().x = sinf(counter);
		//transform.scale1().x = cosf(counter) * 2;
		//transform.scale1().y = sinf(counter) * 2;
		transform.rot1().z = counter;
		transform.rot1().y = counter;
		transform.rot1().x = counter;

		shader.Bind();
		texture.Bind(0);
		//potTexture.Bind(1);
		shader.Update(transform, camera);
		//mesh.Draw();
		loadedMesh.Draw();

		display.Update();

		counter += 0.001f;
	}

	return 0;
}