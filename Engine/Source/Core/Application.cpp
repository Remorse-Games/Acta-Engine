#include "actapch.h"
#include "Application.h"

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

Application::Application()
{
	window = new OpenGLWindow(windowWidth, windowHeight, "Remorse Render Engine");
}

Application::~Application()
{
	delete window;
}

void Application::Start()
{

}

void Application::Update()
{
	window->UpdateWindow();
}
