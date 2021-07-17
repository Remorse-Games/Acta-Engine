#include "actapch.h"
#include "Time.h"

Time::Time()
{

}

Time::~Time()
{
}

void Time::Update()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
