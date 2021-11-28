#include "actapch.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "Objects/Camera/Camera.h"

ActaEngine::Material::Material(const char* vertexFile, const char* fragmentFile)
{
    shader = new OpenGLShader(vertexFile, fragmentFile);
}

ActaEngine::Material::Material(const std::string& vertexFile, const std::string& fragmentFile)
{
    shader = new OpenGLShader(vertexFile.c_str(), fragmentFile.c_str());
}

ActaEngine::Material::~Material()
{
}

void ActaEngine::Material::Bind(MeshRenderer* object)
{
    shader->use();
    shader->SetUniformInt("Texture1", 1);
    shader->SetUniformMat4("model", object->transform.m_Transform);
}
