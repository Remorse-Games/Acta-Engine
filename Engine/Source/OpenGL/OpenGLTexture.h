#pragma once

namespace ActaEngine
{
	class OpenGLTexture
	{
	public:
		OpenGLTexture();
		~OpenGLTexture();

	public:
		/*! List of texture registered. */
		std::vector<unsigned int> textureList;
		/*! Push new texture. 
		* \param textureFile texture file location.
		* \param colorFormat GL type of color format i.e (GL_RGB) */
		void push_texture(const char* textureFile, GLint colorFormat);
		/*! use registered texture.
		* \param index texture index in the vector textureList.
		* \param glTextureNum OpenGL texture index register i.e (GL_TEXTURE0) */
		void use_texture(unsigned int index, GLenum glTextureNum);

	private:
		/*! data of baked texture by stbi_load. */
		unsigned char* data;

		//! texture width.
		int width = 0;
		//! texture height.
		int height = 0;
		//! number of color channels.
		int nrChannels = 0;

		//! texture index.
		unsigned char texture_index = 0;
	};
}