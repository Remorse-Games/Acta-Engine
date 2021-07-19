#include "actapch.h"
#include "OpenGL/OpenGLWindow.h"
//TEST(InitialTest, JustAnExample)
//{
//	EXPECT_EQ(0, 0);
//}

#include "gtest/gtest.h"


int main(int argc, char** argv)
{
	OpenGLWindow* window = new OpenGLWindow(1280, 720, "Remorse Render Engine");
	window->UpdateWindow();
	delete window;
}



