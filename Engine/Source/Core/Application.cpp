#include "actapch.h"
#include "Application.h"
#include "OpenGL/OpenGLWindow.h"
#include "System/Time.h"

unsigned int windowWidth = 1280;
unsigned int windowHeight = 720;

ActaEngine::Application::Application()
{
	OglWindow = new OpenGLWindow(windowWidth, windowHeight, "Acta Engine");
	render = new OpenGLRenderer(OglWindow->window);
	Start();
}

ActaEngine::Application::~Application()
{
	delete OglWindow;
	delete render;
}

void ActaEngine::Application::Start()
{
	spdlog::info("Acta Engine v.0.0.1 Start");
}

void ActaEngine::Application::Update()
{
}

void ActaEngine::Application::EditorUpdate()
{
}

// Run the whole application. This won't be showned in Game Project.
void ActaEngine::Application::Run()
{
	while (!glfwWindowShouldClose(OglWindow->window))
	{
		KeyEvent::ProcessInputKey(OglWindow->window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Time::Update();

		render->Draw();
		Update();
		OglWindow->UpdateWindow();

		render->ImGuiRender([=]() {EditorUpdate(); });

		glfwPollEvents();
		glfwSwapBuffers(OglWindow->window);
	}
}
