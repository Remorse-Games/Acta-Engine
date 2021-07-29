#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace ActaEngine
{
	class MouseEvent
	{
	public:
		static void ProcessInputMouse(GLFWwindow* window, GLenum glButton, GLenum glPress, const bool& isEqual, std::function<void()> func)
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
	};
}