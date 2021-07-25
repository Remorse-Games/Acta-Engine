#pragma once

#include "OpenGL/OpenGLWindow.h"

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

Application* CreateApplication();