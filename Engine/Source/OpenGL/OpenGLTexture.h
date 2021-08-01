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

	private:
		unsigned char* data;
		int width;
		int height;
		int nrChannels;

	};
}