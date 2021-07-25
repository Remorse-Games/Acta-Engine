#include "actapch.h"
#include "Application.h"
#include "OpenGL/OpenGLWindow.h"

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

ActaEngine::Application::Application()
{
	window = new OpenGLWindow(windowWidth, windowHeight, "Remorse Render Engine");
}

ActaEngine::Application::~Application()
{
	delete window;
}

void ActaEngine::Application::Start()
{

}

void ActaEngine::Application::Update()
{
	window->UpdateWindow();
}
