#include "actapch.h"
#include "glad/glad.h"
#include "OpenGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "OpenGLShader.h"

#if defined(ACTA_DEBUG) || (_DEBUG)
#include "OpenGL/OpenGLDebugger.h"
#define glCheckError() glCheckError(__FILE__, __LINE__)
#endif


void ActaEngine::OpenGLTexture::load_texture(const char* str, const std::string& typeName, const std::string& directory)
{
	Texture texture;
	texture.id = TextureFromFile(str, directory, 0);
	texture.type = typeName;
	texture.path = str;
	textures.push_back(texture);
}

void ActaEngine::OpenGLTexture::use_texture(OpenGLShader& shader)
{
	// all of this need to move somewhere else to reduce draw call.
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	//texture setup
	for (int i = 0; i < textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(specularNr++); // transfer unsigned int to string
		}
		else if (name == "texture_normal")
		{
			number = std::to_string(normalNr++); // transfer unsigned int to string
		}
		else if (name == "texture_height")
		{
			number = std::to_string(heightNr++); // transfer unsigned int to string
		}

		shader.use();
		shader.SetUniformInt("material." + name + number, i);

		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

}

unsigned int ActaEngine::OpenGLTexture::TextureFromFile(const char* path, const std::string& directory, bool gamma)
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
		spdlog::warn("Texture failed to load at path: {0}", path);
		stbi_image_free(data);
	}

	return textureID;
}