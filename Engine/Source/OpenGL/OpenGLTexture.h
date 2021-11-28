#pragma once

namespace ActaEngine
{
	class OpenGLTexture
	{
	public:
		OpenGLTexture();
		~OpenGLTexture();

	public:
		std::vector<unsigned int> textureList;
		void push_texture(const char* textureFile, GLint colorFormat);
		void use_texture(unsigned int index, GLenum glTextureNum);

	private:
		unsigned char* data;

		int width = 0;
		int height = 0;
		int nrChannels = 0;

		unsigned char texture_index = 0;
	};
}