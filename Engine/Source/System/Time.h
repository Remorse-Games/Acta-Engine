#pragma once

class Time
{
public:
	Time();
	~Time();

	void Update();

public:
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;
};