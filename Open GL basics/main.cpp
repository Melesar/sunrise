#include "Display.h"
#include "Data/Shader.h"
#include "Components/Mesh.h"
#include "Components/Transform.h"
#include "Components/Camera.h"

#undef main
#include "Data/Texture.h"
#include "Component model/Scene.h";
#include "Component model/GameObject.h"

int main()
{
	Display display(800, 600, "Display");
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Texture potTexture("./res/pot.JPG");
	Transform transform;
	Camera camera (glm::vec3(0, 0, -7), 70.0f, static_cast<float>(800) / 600, 0.01f, 1000.0f);

	Scene scene;

	float counter = 0.0f;

	while(!display.IsClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);

		scene.Update();

		display.Update();

		counter += 0.001f;
	}

	return 0;
}