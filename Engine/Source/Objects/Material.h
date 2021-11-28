#pragma once
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLTexture.h"

namespace ActaEngine
{
	class MeshRenderer;

	class Material
	{

	public:
		Material(const char* vertexFile, const char* fragmentFile);
		Material(const std::string& vertexFile, const std::string& fragmentFile);
		~Material();
		void BindShader(MeshRenderer* object);

	public:
		OpenGLShader* shader;
		OpenGLTexture texture;
	};
}