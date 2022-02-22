#include "actapch.h"
#include "glad/glad.h"
#include "OpenGLTexture.h"
#include "OpenGLShader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#if defined(ACTA_DEBUG) || (_DEBUG)
#include "OpenGL/OpenGLDebugger.h"
#define glCheckError() glCheckError(__FILE__, __LINE__)
#endif

unsigned int ActaEngine::OpenGLTexture::TextureFromFile(const char* path, const std::string& directory)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		spdlog::error("Texture failed to load at path: {0}", path);
		stbi_image_free(data);
	}

	return textureID;

#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}

void ActaEngine::OpenGLTexture::use_texture(unsigned int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
   // glBindTexture(GL_TEXTURE_2D, textures[index].id);
}