#pragma once
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLTexture.h"
#include "Objects/GameObject.h"

namespace ActaEngine
{
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