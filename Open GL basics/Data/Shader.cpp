#include "Shader.h"
#include <fstream>
#include <iostream>
#include "../Components/Transform.h"
#include "../Components/Camera.h"


Shader::Shader(const std::string& fileName)
{
	program = glCreateProgram();
	
	//Vertex shader
	shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);

	//Fragmet shader
	shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (size_t i = 0; i < ShadersAmount; i++)
	{
		glAttachShader(program, shaders[i]);
	}

	//Привязка аттрибута к шейдерной переменной
	glBindAttribLocation(program, 0, "position");
	glBindAttribLocation(program, 1, "texCoord");
	glBindAttribLocation(program, 2, "normal");

	glLinkProgram(program);
	CheckForShaderErrors(program, GL_LINK_STATUS, true, "Error linking program: ");

	glValidateProgram(program);
	CheckForShaderErrors(program, GL_VALIDATE_STATUS, true, "Program is invalid: ");

	uniforms[TRANSFORM_U] = glGetUniformLocation(program, "transform");
	uniforms[DIFFUSE_U]   = glGetUniformLocation(program, "diffuse");
	uniforms[POT_U]		  = glGetUniformLocation(program, "pot");
}


Shader::~Shader()
{
	for (size_t i = 0; i < ShadersAmount; i++)
	{
		glDetachShader(program, shaders[i]);
		glDeleteShader(shaders[i]);
	}

	glDeleteProgram(program);
}

void Shader::Bind()
{
	glUseProgram(program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModelMatrix() ;
	glUniformMatrix4fv(uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);

	glUniform1i(uniforms[DIFFUSE_U], 0);
	glUniform1i(uniforms[POT_U], 1);
}

std::string Shader::LoadShader(const std::string& fileName)
{
	std::ifstream file;
	file.open(fileName.c_str());

	std::string output;
	std::string line;
	if (file.is_open())
	{
		while(file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}else
	{
		std::cerr << "Unable to load shader " << fileName << std::endl;
	}

	return output;
}

void Shader::CheckForShaderErrors(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), nullptr, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), nullptr, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}

GLuint Shader::CreateShader(const std::string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		std::cerr << "Error: Shader creation failed" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	//Присвоение текста шейдера
	glShaderSource(shader, 1 /*количество шейдеров*/, shaderSourceStrings, shaderSourceStringLengths);

	//Компиляция шейдера
	glCompileShader(shader);

	CheckForShaderErrors(shader, GL_COMPILE_STATUS, false, "Error: shader compilation failed: ");

	return shader;
}