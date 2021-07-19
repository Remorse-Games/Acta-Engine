#include "actapch.h"
#include "OpenGLInput.h"

extern unsigned int windowWidth;
extern unsigned int windowHeight;
extern float yaw;
extern float pitch;

bool firstMouse = true;
static float lastMousePosX = windowWidth / 2;
static float lastMousePosY = windowHeight / 2;

void OpenGLInput::ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(window, mouse_callback);
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) != GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) { firstMouse = true; });
	}

	spdlog::info("Last Pos X : {0}, Last Pos Y : {1}", lastMousePosX, lastMousePosY);
}

void OpenGLInput::ProcessInput(GLFWwindow* window, GLenum glKey, GLenum glPress, std::function<void()> func)
{
	if (glfwGetKey(window, glKey) == glPress)
	{
		func();
	}
}

void OpenGLInput::ProcessInput(GLFWwindow* window, GLenum glKey, GLenum glPress, const bool& isEqual, std::function<void()> func)
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

void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastMousePosX = xPos;
		lastMousePosY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastMousePosX;
	float yOffset = lastMousePosY - yPos;
	lastMousePosX = xPos;
	lastMousePosY = yPos;

	const float mouseSensitivity = 0.1f;
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	else if (pitch < -89.0f)
		pitch = -89.0f;
}
