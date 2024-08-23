#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

int num = 1;

int windowSizeX = 640;
int windowSizeY = 480;

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


int main(void)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);

	glfwSetKeyCallback(pWindow, glfwKeyCallback);

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

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(pWindow))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(pWindow);

		/* Poll for and process events */
		glfwPollEvents();

		//glfwSetWindowTitle(pWindow, "Test window:");
	}

	glfwTerminate();
	return 0;
}