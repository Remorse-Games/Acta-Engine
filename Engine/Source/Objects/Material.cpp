#include "actapch.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Objects/Camera/Camera.h"

ActaEngine::Material::Material(const char* vertexFile, const char* fragmentFile)
{
    shaderGL = new OpenGLShader(vertexFile, fragmentFile);
}

ActaEngine::Material::Material(const std::string& vertexFile, const std::string& fragmentFile)
{
    shaderGL = new OpenGLShader(vertexFile.c_str(), fragmentFile.c_str());
}

ActaEngine::Material::~Material()
{
}

void ActaEngine::Material::BindShader(MeshRenderer* object)
{
    shaderGL->use();
    shaderGL->SetUniformInt("Texture1", 1);
    shaderGL->SetUniformMat4("model", object->transform.GetTransformMatrix());
}
