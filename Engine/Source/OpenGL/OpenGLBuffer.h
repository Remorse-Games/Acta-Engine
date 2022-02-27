#pragma once

namespace ActaEngine
{
	struct Vertex;

	class OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBuffer();
		~OpenGLVertexBuffer();

	public:
		void SetData(std::vector<Vertex>& vertices, const unsigned int& vertSize);
		void SetDataF(std::vector<float>& vertices, const unsigned int& vertSize);
		void Bind() const;
		void Unbind() const;

	public:
		unsigned int render_ID;
	};

	class OpenGLIndexBuffer
	{
	public:
		OpenGLIndexBuffer();
		~OpenGLIndexBuffer();

	public:
		void SetData(std::vector<unsigned int>& indices, const unsigned int& indiSize);
		void Bind() const;
		void Unbind() const;

	public:
		unsigned int render_ID;

	};
}