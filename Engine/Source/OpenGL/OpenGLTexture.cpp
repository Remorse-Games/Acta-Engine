#include "actapch.h"
#include "glad/glad.h"
#include "OpenGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#if defined(ACTA_DEBUG) || (_DEBUG)
#include "OpenGL/OpenGLDebugger.h"
#define glCheckError() glCheckError(__FILE__, __LINE__)
#endif

void ActaEngine::OpenGLTexture::push_texture(const char* textureFile, GLint colorFormat)
{
    stbi_set_flip_vertically_on_load(true);

    textureList.push_back(0);
    glGenTextures(1, &textureList[texture_index]);
    glBindTexture(GL_TEXTURE_2D, textureList[texture_index]);

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
    switch (index)
    {
    case 16:
        glActiveTexture(GL_TEXTURE16);
        break; 
    case 15:
        glActiveTexture(GL_TEXTURE15);
        break;
    case 14:
        glActiveTexture(GL_TEXTURE14);
        break;
    case 13:
        glActiveTexture(GL_TEXTURE13);
        break;
    case 12:
        glActiveTexture(GL_TEXTURE12);
        break;
    case 11:
        glActiveTexture(GL_TEXTURE11);
        break;
    case 10:
        glActiveTexture(GL_TEXTURE10);
        break;
    case 9:
        glActiveTexture(GL_TEXTURE9);
        break;
    case 8:
        glActiveTexture(GL_TEXTURE8);
        break;
    case 7:
        glActiveTexture(GL_TEXTURE7);
        break;
    case 6:
        glActiveTexture(GL_TEXTURE6);
        break;
    case 5:
        glActiveTexture(GL_TEXTURE5);
        break;
    case 4:
        glActiveTexture(GL_TEXTURE4);
        break;
    case 3:
        glActiveTexture(GL_TEXTURE3);
        break;
    case 2:
        glActiveTexture(GL_TEXTURE2);
        break;
    case 1:
        glActiveTexture(GL_TEXTURE1);
        break;
    case 0:
        glActiveTexture(GL_TEXTURE0);
        break;
    }
    glBindTexture(GL_TEXTURE_2D, textureList[index]);
}