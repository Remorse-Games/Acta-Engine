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

}

void ActaEngine::OpenGLRenderer::Wireframe()
{
    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ActaEngine::OpenGLRenderer::ImGuiRender(std::function<void()> EditorUpdate)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Rendering");

    ImGui::Checkbox("Wireframe", &wireframe);
    Wireframe();

    ImGui::End();

    EditorUpdate();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}