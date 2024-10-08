#pragma once

#include <iostream>
#include <glad/glad.h>

namespace Renderer
{
	class ShaderProgram
	{
	public:

		ShaderProgram(GLchar* vertexShader, GLchar* fragmentShader, GLuint& shader_program);
	
	private:

		GLuint CreateShader(GLenum shaderType, GLchar* shaderText);

		bool isCompiled = false;

	};
}