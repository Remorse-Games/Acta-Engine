#include "actapch.h"
#include "Material.h"
#include "Mesh.h"
#include "Objects/Camera/Camera.h"

ActaEngine::Material::Material(const char* vertexFile, const char* fragmentFile)
{
    shaderGL = std::make_unique<OpenGLShader>(vertexFile, fragmentFile);
    textureGL = std::make_unique<OpenGLTexture>();
}

ActaEngine::Material::Material(const std::string& vertexFile, const std::string& fragmentFile)
{
    shaderGL = std::make_unique<OpenGLShader>(vertexFile.c_str(), fragmentFile.c_str());
    textureGL = std::make_unique<OpenGLTexture>();
}

ActaEngine::Material::~Material()
{
}
