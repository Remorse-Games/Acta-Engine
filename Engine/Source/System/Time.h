#pragma once

namespace ActaEngine
{
	class Time
	{
	public:
		static float deltaTime;
		static float lastFrame;

		static void Update();
	};
}