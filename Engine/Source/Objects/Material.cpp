#include "actapch.h"
#include "Material.h"

void ActaEngine::Material::Init()
{
	shader = new OpenGLShader("Shader/triangle.vert", "Shader/triangle.frag");
}

void ActaEngine::Material::Bind(GameObject* object)
{
    shader->use();
    shader->SetUniformInt("Texture1", 1);
    shader->SetUniformMat4("model", object->transform.m_Transform);
}


