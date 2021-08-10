#pragma once
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLTexture.h"

namespace ActaEngine
{
	class GameObject;

	class Material
	{
	public:
		Material(const char* vertexFile, const char* fragmentFile);
		Material(const std::string& vertexFile, const std::string& fragmentFile);
		~Material();
		void Bind(GameObject* object);
	public:
		OpenGLShader* shader;
		OpenGLTexture texture;
	};
}