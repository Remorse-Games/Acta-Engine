#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Core/Events/KeyEvent.h"
#include "OpenGL/OpenGLRenderer.h"
#include "ImGui/ImGui_Main.h"
#include "Objects/Camera/Camera.h"

void resize_callback(GLFWwindow* window, int width, int height);

namespace ActaEngine
{
	class OpenGLWindow
	{
	public:
		OpenGLWindow(unsigned int width, unsigned int height, std::string&& title);
		~OpenGLWindow();

		void UpdateWindow();
		
		GLFWwindow* window;
		Camera* mainCamera;

	private:
#if defined(ACTA_DEBUG) || defined(ACTA_DEV)
		ImGui_Main imgui;
#endif
	};
}
