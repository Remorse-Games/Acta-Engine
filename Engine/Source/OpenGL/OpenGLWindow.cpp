#include "actapch.h"
#include "OpenGLWindow.h"
#include "System/Time.h"

ActaEngine::OpenGLWindow::OpenGLWindow(unsigned int width, unsigned int height, std::string&& title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Init GLFW
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL)
	{
		spdlog::error("GLFW not initialize");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resize_callback);

	// Init Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		spdlog::error("GLAD not initialize");
	}

	glEnable(GL_DEPTH_TEST);
	mainCamera = new Camera();
	glfwSetWindowUserPointer(window, mainCamera);

	int nrAttrib;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttrib);
	spdlog::info("Maximum number of vertex attributes supported : {0}", nrAttrib);

	spdlog::info("Vendor	: {0}", glGetString(GL_VENDOR));
	spdlog::info("Renderer	: {0}", glGetString(GL_RENDERER));
	spdlog::info("Version	: {0}", glGetString(GL_VERSION));
}

ActaEngine::OpenGLWindow::~OpenGLWindow()
{
	delete mainCamera;
	glfwTerminate();
}

void ActaEngine::OpenGLWindow::UpdateWindow()
{
	mainCamera->Draw();
	mainCamera->Input(window);
}

void resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

