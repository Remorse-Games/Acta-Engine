#include "actapch.h"
#include "glad/glad.h"
#include "Mesh.h"
#include "Material.h"

#if defined(ACTA_DEBUG) || (_DEBUG)
#include "OpenGL/OpenGLDebugger.h"
#define glCheckError() glCheckError(__FILE__, __LINE__)
#endif

ActaEngine::Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    m_indices = indices;

    vertexBuffer.SetData(vertices, vertices.size() * sizeof(Vertex));
    indexBuffer.SetData(indices, indices.size() * sizeof(unsigned int));
    vertexBuffer.Bind();
    indexBuffer.Bind();

#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif

}

ActaEngine::Mesh::~Mesh()
{

}

void ActaEngine::Mesh::Draw(OpenGLShader& shader)
{

    //draw all data that has been setup
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(m_indices.size()), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);

    // only need declared once, it will populate all errors happened in
    // one block.
#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}