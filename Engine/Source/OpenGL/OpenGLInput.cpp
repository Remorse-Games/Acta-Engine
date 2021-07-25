#include "actapch.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "OpenGLInput.h"

void OpenGLInput::ProcessInputKey(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void OpenGLInput::ProcessInputKey(GLFWwindow* window, GLenum glKey, GLenum glPress, const bool& isEqual, std::function<void()> func)
{
	if (isEqual)
	{
		if (glfwGetKey(window, glKey) == glPress)
		{
			func();
		}
	}
	else
	{
		if (glfwGetKey(window, glKey) != glPress)
		{
			func();
		}
	}
}

void OpenGLInput::ProcessInputMouse(GLFWwindow* window, GLenum glButton, GLenum glPress, const bool& isEqual, std::function<void()> func)
{
	if (isEqual)
	{
		if (glfwGetMouseButton(window, glButton) == glPress)
		{
			func();
		}
	}
	else
	{
		if (glfwGetMouseButton(window, glButton) != glPress)
		{
			func();
		}
	}
}