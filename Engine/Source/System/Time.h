#pragma once

struct Time
{
	static float deltaTime;
	static float lastFrame;

	static void Update()
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}
};

