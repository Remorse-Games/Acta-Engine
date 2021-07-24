#include "actapch.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Time.h"

float Time::deltaTime;
float Time::lastFrame;

void Time::Update()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
