#include "actapch.h"
#include "glad/glad.h"
#include "OpenGLRenderer.h"

ActaEngine::OpenGLRenderer::OpenGLRenderer(GLFWwindow* window) :
    wireframe(false)
{
#if defined(ACTA_DEBUG) || defined(ACTA_DEV)
    imgui.Init(window);
#endif
}

ActaEngine::OpenGLRenderer::~OpenGLRenderer()
{
#if defined(ACTA_DEBUG) || defined(ACTA_DEV)
    imgui.Destroy();
#endif
}

void ActaEngine::OpenGLRenderer::Draw()
{
    //OglWindow->mainCamera->Draw();

    //go.Draw();
    //go1.Draw();
    //go2.Draw();

    //OglWindow->mainCamera->Bind(&go.material);

    //go.material.shader->use();

    //imgui.Render([=]() {ImGuiRender(); });
}

void ActaEngine::OpenGLRenderer::Wireframe()
{
    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ActaEngine::OpenGLRenderer::ImGuiRender()
{
    ImGui::Begin("Rendering");

    ImGui::Checkbox("Wireframe", &wireframe);
    Wireframe();

    ImGui::End();
}