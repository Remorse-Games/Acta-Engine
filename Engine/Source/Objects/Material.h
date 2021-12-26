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
		/*! Bind Shader to the mesh renderer. */
		void BindShader(MeshRenderer* object);

	public:
		/*! Shader container using OpenGL. */
		OpenGLShader* shaderGL;
		/*! Texture container using OpenGL. */
		OpenGLTexture textureGL;
	};
}