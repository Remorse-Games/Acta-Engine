#pragma once
#include "Objects/Material.h"
#include "OpenGL/OpenGLBuffer.h"
#include "OpenGL/OpenGLShader.h"

#define MAX_BONE_INFLUENCE 4

namespace ActaEngine
{
	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	struct Vertex {
		// position
		glm::vec3 Position;
		// normal
		glm::vec3 Normal;
		// texCoords
		glm::vec2 TexCoords;
		// tangent
		glm::vec3 Tangent;
		// bitangent
		glm::vec3 Bitangent;
		//bone indexes which will influence this vertex
		int m_BoneIDs[MAX_BONE_INFLUENCE];
		//weights from each bone
		float m_Weights[MAX_BONE_INFLUENCE];
	};

	class MeshRenderer
	{
	public:
		MeshRenderer(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures);
		~MeshRenderer();

	public:
		/*! Drawing object inside renderer. */
		void Draw(OpenGLShader& shader);


	private:
		/*! Vertex Buffer process. */
		OpenGLVertexBuffer vertexBuffer;
		/*! Index Buffer process. */
		OpenGLIndexBuffer indexBuffer;
		/*! Vertex Array Object data. */
		unsigned int vao;

		std::vector<Texture> m_textures;
		std::vector<unsigned int> m_indices;
	};
}