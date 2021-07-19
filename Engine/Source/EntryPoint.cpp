#include "actapch.h"
#include "OpenGL/OpenGLWindow.h"

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

int main()
{
	OpenGLWindow* window = new OpenGLWindow(1280, 720, "Remorse Render Engine");
	window->UpdateWindow();
	delete window;
}