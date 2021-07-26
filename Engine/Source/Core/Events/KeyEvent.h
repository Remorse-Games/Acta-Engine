#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace ActaEngine
{
	class KeyEvent
	{
	public:
		static void ProcessInputKey(GLFWwindow* window)
		{
			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(window, true);
			}
		}

		static void ProcessInputKey(GLFWwindow* window, GLenum glKey, GLenum glPress, const bool& isEqual, std::function<void()> func)
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
	};
}