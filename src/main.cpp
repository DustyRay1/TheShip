#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>

#include "Renderer/ShaderProgram.h" //Renderer here cause ShaderProgram.h is in another folder

//using namespace Proverka;

GLuint* points_vbo_link = nullptr;

GLfloat point[] = {
	 0.0f, 0.3f,
	 0.1f, 0.0f,
	 -0.1f,0.0f,
};

GLfloat colors[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
};

GLchar* vertex_shader =
"#version 460\n"
"layout(location = 0) in vec2 vertex_position;"
"layout(location = 1) in vec3 vertex_color;"
"out vec3 color;"
"void main() {"
"   color = vertex_color;"
"   gl_Position = vec4(vertex_position, 0.0 , 1.0);"
"}";

GLchar* fragment_shader =
"#version 460\n"
"in vec3 color;"
"out vec4 frag_color;"
"void main() {"
"   frag_color = vec4(color, 1.0);"
"}";


int windowSizeX = 640;
int windowSizeY = 420;

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
	windowSizeX = width;
	windowSizeY = height;
	glViewport(0, 0, windowSizeX, windowSizeY);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(pWindow, true);
	}
}
	
void glfwHoldCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		point[0] += 0.1f;
		std::cout << std::to_string(point[0]);
		glBindBuffer(GL_ARRAY_BUFFER, *points_vbo_link); //Активным может быть только 1 буфер
		glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
	}
}


int main(void)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Check();

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* pWindow = glfwCreateWindow(windowSizeX, windowSizeY, "TheShip", nullptr, nullptr);

	if (!pWindow)
	{
		glfwTerminate();
		return -1;
	}

	//glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);

	glfwSetKeyCallback(pWindow, glfwKeyCallback);

	glfwSetKeyCallback(pWindow, glfwHoldCallback);

	/* Make the window's context current */
	glfwMakeContextCurrent(pWindow);

	if (!gladLoadGL())
	{
		std::cout << "Cant load GLAD!" << std::endl;
		return -1;
	}
	std::cout << "GL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "GL Version: " << glGetString(GL_VERSION) << std::endl;

	std::cout << "GLAD_VERSION" << GLVersion.major << "." << GLVersion.minor;

	glClearColor(1, 1, 0, 1);

	//GLuint x = 0;

	GLuint shader_program {};
	
	Renderer::ShaderProgram::ShaderProgram(vertex_shader, fragment_shader, shader_program); //Мы можем вызвать 

	Renderer::ShaderProgram someshader(vertex_shader, fragment_shader, shader_program);

	//GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vs, 1, &vertex_shader, nullptr);
	//glCompileShader(vs);

	//GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fs, 1, &fragment_shader, nullptr);
	//glCompileShader(fs);

	//GLuint shader_program = glCreateProgram();
	//glAttachShader(shader_program, vs);
	//glAttachShader(shader_program, fs);
	//glLinkProgram(shader_program);

	//glDeleteShader(vs);
	//glDeleteShader(fs);

	GLuint points_vbo = 0;
	glGenBuffers(1, &points_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
	points_vbo_link = &points_vbo;

	GLuint colors_vbo = 0;
	glGenBuffers(1, &colors_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, points_vbo); //Активным может быть только 1 буфер
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(pWindow))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//colors[11] += 0.01f;
		glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

		//point[0] += 0.001f;
		////std::cout << std::to_string(point[0]);
		//glBindBuffer(GL_ARRAY_BUFFER, points_vbo); //Активным может быть только 1 буфер
		//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glUseProgram(shader_program);
		glBindVertexArray(vao);
		glDrawArrays(GL_POLYGON, 0, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);

		/* Poll for and process events */
		glfwPollEvents();

		//glfwSetWindowTitle(pWindow, "Test window:");
	}

	glfwTerminate();
	return 0;
}