#include "ShaderProgram.h"

//using namespace Renderer;

	Renderer::ShaderProgram::ShaderProgram(GLchar* vertexShader, GLchar* fragmentShader, GLuint& shader_program_outer)
	{
		GLuint vs = CreateShader(GL_VERTEX_SHADER, vertexShader);

		GLuint fs = CreateShader(GL_FRAGMENT_SHADER, fragmentShader);

		GLuint shader_program_inner = glCreateProgram();
		glAttachShader(shader_program_inner, vs);
		glAttachShader(shader_program_inner, fs);
		glLinkProgram(shader_program_inner);

		shader_program_outer = shader_program_inner;

		glDeleteShader(vs);
		glDeleteShader(fs);

		isCompiled = true; //Pochemu ya imeyu dostup?
	}

	GLuint Renderer::ShaderProgram::CreateShader(GLenum shaderType, GLchar* shaderText)
	{
		GLuint ID = glCreateShader(shaderType);
		glShaderSource(ID, 1, &shaderText, nullptr);
		glCompileShader(ID);
		return ID;
	}


