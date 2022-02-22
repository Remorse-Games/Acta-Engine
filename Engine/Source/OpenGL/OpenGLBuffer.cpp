#include "actapch.h"
#include "glad/glad.h"
#include "OpenGLBuffer.h"
#include "OpenGL/OpenGLShader.h"
#include "Objects/MeshRenderer.h"

#if defined(ACTA_DEBUG) || (_DEBUG)
#include "OpenGL/OpenGLDebugger.h"
#define glCheckError() glCheckError(__FILE__, __LINE__)
#endif

///////////////////////////////////////////////////////////////////////////
////////////////////////  VERTEX BUFFER //////////////////////////////////
/////////////////////////////////////////////////////////////////////////

ActaEngine::OpenGLVertexBuffer::OpenGLVertexBuffer()
    : render_ID(0)
{
    glGenBuffers(1, &render_ID);

#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}

ActaEngine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
    glDeleteBuffers(1, &render_ID);
}

void ActaEngine::OpenGLVertexBuffer::SetData(std::vector<Vertex>& vertices, const unsigned int& vertSize)
{
    glBindBuffer(GL_ARRAY_BUFFER, render_ID);
    glBufferData(GL_ARRAY_BUFFER, vertSize, &vertices[0], GL_STATIC_DRAW);

#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}

void ActaEngine::OpenGLVertexBuffer::SetDataF(std::vector<float>& vertices, const unsigned int& vertSize)
{
    glBindBuffer(GL_ARRAY_BUFFER, render_ID);
    glBufferData(GL_ARRAY_BUFFER, vertSize, &vertices[0], GL_STATIC_DRAW);

#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}

void ActaEngine::OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, render_ID);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    // vertex tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    // vertex bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
    // ids
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneIDs));

    // weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Weights));
    glBindVertexArray(0);

#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif

}

void ActaEngine::OpenGLVertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

///////////////////////////////////////////////////////////////////////////
////////////////////////  INDEX BUFFER ///////////////////////////////////
/////////////////////////////////////////////////////////////////////////

ActaEngine::OpenGLIndexBuffer::OpenGLIndexBuffer()
    : render_ID(0)
{
    glGenBuffers(1, &render_ID);
#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}

ActaEngine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
    glDeleteBuffers(1, &render_ID);
}

void ActaEngine::OpenGLIndexBuffer::SetData(std::vector<unsigned int>& indices, const unsigned int& indiSize)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiSize, &indices[0], GL_STATIC_DRAW);
#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}

void ActaEngine::OpenGLIndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_ID);
#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}

void ActaEngine::OpenGLIndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
