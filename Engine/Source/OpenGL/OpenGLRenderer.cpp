#include "actapch.h"
#include "glad/glad.h"
#include "OpenGLRenderer.h"

ActaEngine::OpenGLRenderer::OpenGLRenderer() :
    wireframe(false)
{
}

ActaEngine::OpenGLRenderer::~OpenGLRenderer()
{
}

void ActaEngine::OpenGLRenderer::Draw()
{
}

void ActaEngine::OpenGLRenderer::Wireframe()
{
    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
