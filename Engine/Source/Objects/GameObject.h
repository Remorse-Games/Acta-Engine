#pragma once
#include "Transform.h"
#include "OpenGL/OpenGLBuffer.h"
#include "OpenGL/OpenGLTexture.h"
#include "OpenGL/OpenGLShader.h"

namespace ActaEngine
{
	class GameObject : public Transform
	{
	public:
		GameObject();
		~GameObject();

	public:
		void Draw();

	public:
		OpenGLTexture texture;
		OpenGLShader shader;

	private:
		OpenGLVertexBuffer vertexBuffer;
		OpenGLIndexBuffer indexBuffer;
		unsigned int vao;
		unsigned int vbo;
	};
}