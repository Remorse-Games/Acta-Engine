#pragma once

#include "OpenGL/OpenGLWindow.h"

namespace ActaEngine
{
	class Application
	{
	public:
		Application();
		~Application();

		void Start();
		void Update();

	private:
		OpenGLWindow* window;
	};
}

ActaEngine::Application* CreateApplication();