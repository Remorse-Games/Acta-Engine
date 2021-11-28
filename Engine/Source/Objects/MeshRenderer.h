#pragma once
#include "Transform.h"
#include "Objects/Material.h"
#include "OpenGL/OpenGLBuffer.h"
#include "OpenGL/OpenGLTexture.h"
#include "OpenGL/OpenGLShader.h"

namespace ActaEngine
{
	class MeshRenderer
	{
	public:
		MeshRenderer();
		~MeshRenderer();

	public:
		void Init(Material* material);
		void Draw(Material* material);

	public:
		Transform transform;

	private:
		OpenGLVertexBuffer vertexBuffer;
		OpenGLIndexBuffer indexBuffer;
		unsigned int vao;
		unsigned int vbo;

	public:
		std::vector<float> vertices;
		std::vector<float> indices;

	private:
		glm::mat4 model;
	};
}