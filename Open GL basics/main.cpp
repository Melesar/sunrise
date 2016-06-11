#include "Display.h"
#include "Data/Shader.h"
#include "Components/Mesh.h"
#include "Components/Transform.h"
#include "Components/Camera.h"

#undef main
#include "Data/Texture.h"
#include "Component model/Scene.h";
#include "Component model/GameObject.h"
#include "Application.h"

int main()
{
	/*Display display(800, 600, "Display");
	Shader shader("./res/basicShader");
	Texture texture("./res/bricks.jpg");
	Texture potTexture("./res/pot.JPG");
	Transform transform;
	Camera camera;

	Scene scene;

	while(!display.IsClosed())
	{
		shader.Bind();
		texture.Bind(0);
		shader.Update(transform, camera);

		scene.Update();

		display.Update();
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
	}*/

	Application::Start();
	Scene scene;

	while (Application::IsActive()) {
		scene.Update();
		Application::Update();
	}

	return 0;
}