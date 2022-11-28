#include "actapch.h"
#include "glad/glad.h"
#if defined(ACTA_RELEASE)
#include "GLFW/glfw3.h"
#endif
#include "OpenGLRenderer.h"

ActaEngine::OpenGLRenderer::OpenGLRenderer(GLFWwindow* window) :
    wireframe(false),
    imgui(window)
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

#if defined(ACTA_DEBUG) || defined(ACTA_DEV)
void ActaEngine::OpenGLRenderer::ImGuiRender(std::function<void()> EditorUpdate)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Rendering");

    ImGui::Checkbox("Wireframe", &wireframe);
    Wireframe();

    ImGui::End();

    // TODO: uncomment this later when I already implement viewport for game.
//    ImGui::Begin("Game View");
    //ImGui::DockSpaceOverViewport();
    //if (ImGui::BeginMainMenuBar()) 
    //{
    //    if (ImGui::BeginMenu("File")) {
    //        ImGui::EndMenu();
    //    }
    //    if (ImGui::BeginMenu("Edit")) {
    //        ImGui::EndMenu();
    //    }
    //    ImGui::EndMainMenuBar();
    //}
 //   ImGui::End();

    EditorUpdate();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
#endif