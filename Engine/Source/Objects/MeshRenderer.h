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
		/*! Initialize VBO, VAO and EBO, shader to start creating the object. */
		void Init(Material& material);
		/*! Drawing object inside renderer. */
		void Draw(Material& material);

	public:
		/*! Transform object to manipulate object transform. */
		Transform transform;

	private:
		/*! Vertex Buffer process. */
		OpenGLVertexBuffer vertexBuffer;
		/*! Index Buffer process. */
		OpenGLIndexBuffer indexBuffer;
		/*! Vertex Array Object data. */
		unsigned int vao;
		/*! Vertex Buffer Object data. */
		unsigned int vbo;

	protected:
		/*! Storing the vertices inside vector. */
		std::vector<float> vertices;
		/*! Storing indices inside vector. */
		std::vector<float> indices;
	};
}