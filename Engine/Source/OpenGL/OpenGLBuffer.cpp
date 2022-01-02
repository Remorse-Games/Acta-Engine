#include "actapch.h"
#include "glad/glad.h"
#include "OpenGLBuffer.h"
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLTexture.h"

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

void ActaEngine::OpenGLVertexBuffer::SetData(void* vertices, const unsigned int& vertSize)
{
    glBindBuffer(GL_ARRAY_BUFFER, render_ID);

    glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

#if (defined(ACTA_DEBUG) || (_DEBUG))
    OpenGLDebugger::glCheckError();
#endif
}

void ActaEngine::OpenGLVertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, render_ID);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

void ActaEngine::OpenGLIndexBuffer::SetData(void* indices, const unsigned int& indiSize)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiSize, indices, GL_STATIC_DRAW);
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
