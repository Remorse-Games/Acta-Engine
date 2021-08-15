#pragma once
#include "Transform.h"
#include "Objects/Material.h"
#include "OpenGL/OpenGLBuffer.h"
#include "OpenGL/OpenGLTexture.h"
#include "OpenGL/OpenGLShader.h"

namespace ActaEngine
{
	class GameObject
	{
	public:
		GameObject(Material* material);
		~GameObject();

	public:
		void Draw(Material* material);

	public:
		Transform transform;

	private:
		OpenGLVertexBuffer vertexBuffer;
		OpenGLIndexBuffer indexBuffer;
		unsigned int vao = 0;
		unsigned int vbo = 0;

	private:
		glm::mat4 model = glm::mat4(0.0f);
	};
}