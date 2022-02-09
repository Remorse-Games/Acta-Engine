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

void ActaEngine::OpenGLTexture::push_texture(const char* textureFile, GLint colorFormat, const std::string& textureType)
{
    stbi_set_flip_vertically_on_load(true);

    Texture texture = { texture_index, textureType };
    textures.push_back(texture);
    glGenTextures(1, &textures[texture_index].id);
    glBindTexture(GL_TEXTURE_2D, textures[texture_index].id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load(textureFile, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, colorFormat, width, height, 0, colorFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        spdlog::error("Failed to load Texture %d", texture_index);
    }

    texture_index++;

    stbi_image_free(data);

#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}

void ActaEngine::OpenGLTexture::use_texture(unsigned int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, textures[index].id);
}