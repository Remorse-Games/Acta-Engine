#pragma once

#include "OpenGL/OpenGLWindow.h"

namespace ActaEngine
{
	class Application
	{
	public:
		Application();
		~Application();

		virtual void Start();
		virtual void Update();

	private:
		OpenGLWindow* window;
	};
}

ActaEngine::Application* CreateApplication();