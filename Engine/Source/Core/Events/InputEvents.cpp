#include "actapch.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "InputEvents.h"

void ActaEngine::InputEvents::ProcessInputKey(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void ActaEngine::InputEvents::ProcessInputKey(GLFWwindow* window, GLenum glKey, GLenum glPress, const bool& isEqual, std::function<void()> func)
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

void ActaEngine::InputEvents::ProcessInputMouse(GLFWwindow* window, GLenum glButton, GLenum glPress, const bool& isEqual, std::function<void()> func)
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