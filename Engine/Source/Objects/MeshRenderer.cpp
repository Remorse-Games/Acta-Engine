#include "actapch.h"
#include "glad/glad.h"
#include "MeshRenderer.h"
#include "Material.h"

#if defined(ACTA_DEBUG) || (_DEBUG)
#include "OpenGL/OpenGLDebugger.h"
#define glCheckError() glCheckError(__FILE__, __LINE__)
#endif

ActaEngine::MeshRenderer::MeshRenderer(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture>& textures)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vertexBuffer.SetData(vertices, vertices.size() * sizeof(Vertex));
    indexBuffer.SetData(indices, indices.size() * sizeof(unsigned int));
    vertexBuffer.Bind();
    indexBuffer.Bind();

#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif

}

ActaEngine::MeshRenderer::~MeshRenderer()
{

}

void ActaEngine::MeshRenderer::Draw(Material& material)
{
    //transform into shader
    material.shaderGL->use();
    material.shaderGL->SetUniformMat4("model", transform.GetTransformMatrix());

    //texture setup
    if (material.textureGL != nullptr)
    {
        for (int i = 0; i < material.textureGL->textureList.size(); ++i)
        {
            material.textureGL->use_texture(i);
        }

        material.shaderGL->use();
        material.shaderGL->SetUniformInt("material.diffuse", 0);
        material.shaderGL->SetUniformInt("material.specular", 1);
    }

    //draw all data that has been setup
    glBindVertexArray(vao);
    //glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    // only need declared once, it will populate all errors happened in
    // one block.
#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}
