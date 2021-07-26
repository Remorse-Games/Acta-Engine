#pragma once

#include "OpenGL/OpenGLWindow.h"
#include "Objects/Camera/Camera.h"
namespace ActaEngine
{
	class Application
	{
	public:
		Application();
		~Application();

		virtual void Start();
		virtual void Update();

		void Run();

	private:
		OpenGLWindow* OglWindow;
		OpenGLRenderer* render;
	};
}

ActaEngine::Application* CreateApplication();