#include "actapch.h"
#include "OpenGL/OpenGLWindow.h"

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

float yaw = -90.0f;
float pitch = 0.0f;

int main()
{
	OpenGLWindow* window = new OpenGLWindow(1280, 720, "Remorse Render Engine");
	window->UpdateWindow();
	delete window;
}