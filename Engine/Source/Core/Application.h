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
		virtual void EditorUpdate();
		void Run();

		OpenGLWindow* OglWindow;

	private:
		OpenGLRenderer* render;

	};
}

ActaEngine::Application* CreateApplication();