#pragma once
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLTexture.h"

namespace ActaEngine
{
	class Mesh;

	class Material
	{

	public:
		Material(const char* vertexFile, const char* fragmentFile);
		Material(const std::string& vertexFile, const std::string& fragmentFile);
		Material() = delete;
		~Material();

	public:
		/*! Shader container using OpenGL. */
		std::unique_ptr<OpenGLShader> shaderGL;
		/*! Texture container using OpenGL. */
		std::unique_ptr <OpenGLTexture> textureGL;
	};
}