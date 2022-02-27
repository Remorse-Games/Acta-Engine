#include "actapch.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Time.h"

float ActaEngine::Time::deltaTime;
float ActaEngine::Time::lastFrame;

void ActaEngine::Time::Update()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

void ActaEngine::Time::ProcessTimeLoad(std::function<void()> process)
{
}
