#pragma once

namespace ActaEngine
{
	class OpenGLDebugger
	{
	public:

		static GLenum glCheckError(const char* file, int line);
	};
}