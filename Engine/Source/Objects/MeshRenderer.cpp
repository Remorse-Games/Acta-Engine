#include "actapch.h"
#include "glad/glad.h"
#include "MeshRenderer.h"
#include "Material.h"

#if defined(ACTA_DEBUG) || (_DEBUG)
#include "OpenGL/OpenGLDebugger.h"
#define glCheckError() glCheckError(__FILE__, __LINE__)
#endif

ActaEngine::MeshRenderer::MeshRenderer()
{
 
}

ActaEngine::MeshRenderer::~MeshRenderer()
{

}

void ActaEngine::MeshRenderer::Init(Material* material)
{
    //unsigned int indices[] = {
    //    0, 1, 3, // first triangle
    //    1, 2, 3  // second triangle
    //};

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    vertexBuffer.SetData(vertices.data(), vertices.size() * sizeof(float));
    //indexBuffer.SetData(indices, sizeof(indices));
    vertexBuffer.Bind();
    //indexBuffer.Bind();

    material->shaderGL->use();
    material->shaderGL->SetUniformMat4("model", transform.GetTransformMatrix());

#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}

void ActaEngine::MeshRenderer::Draw(Material* material)
{
    //vertex setup
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.render_ID);
    vertexBuffer.Bind();

    //transform into shader
    material->shaderGL->SetUniformMat4("model", transform.GetTransformMatrix());

    //texture setup
    material->textureGL.use_texture(0, GL_TEXTURE0);
    material->textureGL.use_texture(1, GL_TEXTURE1);

    material->shaderGL->SetUniformInt("Texture1", 1);

    //draw all data that has been setup
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    // only need declared once, it will populate all errors happened in
    // one block.
#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}
