#pragma once
#include "Transform.h"
#include "OpenGL/OpenGLBuffer.h"
#include "OpenGL/OpenGLTexture.h"
#include "OpenGL/OpenGLShader.h"

namespace ActaEngine
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

	public:
		void Draw();

	public:
		Transform transform;
		Material material;
	private:
		OpenGLVertexBuffer vertexBuffer;
		OpenGLIndexBuffer indexBuffer;
		unsigned int vao;
		unsigned int vbo;

	private:
		glm::mat4 model;
	};
}