#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core/Events/InputEvents.h"
#include "OpenGL/OpenGLRenderer.h"
#include "ImGui/ImGui_Main.h"

void resize_callback(GLFWwindow* window, int width, int height);
namespace ActaEngine
{
	class OpenGLWindow
	{
	public:
		OpenGLWindow(unsigned int width, unsigned int height, std::string&& title);
		~OpenGLWindow();

		void UpdateWindow();

	private:
		GLFWwindow* window;
		ImGui_Main imgui;
		OpenGLRenderer* render;
	};
}
