#pragma once
#include <string>
#include <GL/glew.h>

class Transform;
class Camera;

class Shader
{
public:
	Shader(const std::string& fileName);
	virtual ~Shader();

	void Bind();

	void Update(const Transform& transform, const Camera& camera);

private:
	static unsigned const int ShadersAmount = 2;

	std::string LoadShader(const std::string& fileName);
	void CheckForShaderErrors(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, GLenum shaderType);

	enum
	{
		TRANSFORM_U,
		DIFFUSE_U,
		POT_U,

		NUM_UNIFORMS
	};

	GLuint program;
	GLuint shaders[ShadersAmount];
	GLuint uniforms[NUM_UNIFORMS];
};

