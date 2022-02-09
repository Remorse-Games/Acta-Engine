#pragma once
#include "Transform.h"
#include "Objects/Material.h"
#include "OpenGL/OpenGLBuffer.h"
#include "OpenGL/OpenGLTexture.h"
#include "OpenGL/OpenGLShader.h"

namespace ActaEngine
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class MeshRenderer
	{
	public:
		MeshRenderer(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
		MeshRenderer(std::vector<float>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
		~MeshRenderer();

	public:
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

	protected:
		/*! Storing the vertices inside vector. */
		std::vector<float> m_vertices;
		/*! Storing indices inside vector. */
		std::vector<unsigned int> m_indices;
	};
}