#pragma once

namespace ActaEngine
{
	class InputEvents
	{
	public:
		static void ProcessInputKey(GLFWwindow* window);
		static void ProcessInputKey(GLFWwindow* window, GLenum glKey, GLenum glPress, const bool& isEqual, std::function<void()> func);
		static void ProcessInputMouse(GLFWwindow* window, GLenum glButton, GLenum glPress, const bool& isEqual, std::function<void()> func);
	};
}