#pragma once
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLTexture.h"

namespace ActaEngine
{
	class GameObject;

	class Material
	{
	public:
		void Init();
		void Bind(GameObject* object);
	public:
		OpenGLShader* shader;
		OpenGLTexture texture;
	};
}