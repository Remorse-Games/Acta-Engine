#pragma once

namespace ActaEngine
{
	class OpenGLRenderer
	{
	public:
		OpenGLRenderer();
		~OpenGLRenderer();

	public:
		void Draw();
		void Wireframe();

	private:
		bool wireframe;

	};
}