#include "actapch.h"
#include "OpenGL/OpenGLWindow.h"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define UNIT_TESTING false
#if !UNIT_TESTING
int main(int argc, char** argv)
{
	OpenGLWindow* window = new OpenGLWindow(windowWidth, windowHeight, "Remorse Render Engine");
	window->UpdateWindow();
	delete window;
}
#endif



