#include "actapch.h"
#include "OpenGL/OpenGLWindow.h"
//TEST(InitialTest, JustAnExample)
//{
//	EXPECT_EQ(0, 0);
//}
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define CATCH_CONFIG_MAIN
#define UNIT_TESTING 1

#if !UNIT_TESTING
int main(int argc, char** argv)
{
	OpenGLWindow* window = new OpenGLWindow(1280, 720, "Remorse Render Engine");
	window->UpdateWindow();
	delete window;
}
#endif



