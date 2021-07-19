#pragma once

void mouse_callback(GLFWwindow* window, double xPos, double yPos);

class OpenGLInput
{
public:
	static void ProcessInput(GLFWwindow* window);
	static void ProcessInput(GLFWwindow* window, GLenum glKey, GLenum glPress, std::function<void()> func);
	static void ProcessInput(GLFWwindow* window, GLenum glKey, GLenum glPress, const bool& isEqual, std::function<void()> func);
};
