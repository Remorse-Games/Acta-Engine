#pragma once

namespace ActaEngine
{
	class OpenGLShader;

	struct Texture {
		unsigned int id;
		std::string type;
		std::string path;
	};

	class OpenGLTexture
	{
	public:
		std::vector<Texture> textures;
		/*! Push new texture. 
		* \param textureFile texture file location.
		* \param colorFormat GL type of color format i.e (GL_RGB) */
		unsigned int TextureFromFile(const char* path, const std::string& directory);
		/*! use registered texture.
		* \param index texture index in the vector textureList.
		* \param glTextureNum OpenGL texture index register i.e (GL_TEXTURE0) */
		void use_texture(unsigned int index);
		float mix = 0.5f;

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