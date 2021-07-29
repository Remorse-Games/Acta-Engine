#include "ActaEngine.h"

using namespace ActaEngine;

class Game : public ActaEngine::Application
{
public:
    ActaEngine::GameObject go;
    ActaEngine::GameObject go1;
    ActaEngine::GameObject go2;

	Game()
	{
        Start();
    }

	~Game()
	{

    }

	void Start() override
	{
        spdlog::info("Start the game!");
        go.transform.Identity();
        go.transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

        go1.transform.Identity();
        go1.transform.SetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
       
        go2.transform.Identity();
        go2.transform.SetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
    }

	void Update() override
	{
        // This should be inside renderer when do draw etc
        OglWindow->mainCamera->Draw();
        
        go.Draw();
        go1.Draw();
        go2.Draw();

        OglWindow->mainCamera->Bind(&go.material);

        go.material.shader->use();
        // until here

        // ImGui region
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Camera");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        float camPos[] = { OglWindow->mainCamera->transform.GetPosition().x, OglWindow->mainCamera->transform.GetPosition().y, OglWindow->mainCamera->transform.GetPosition().z };
        ImGui::InputFloat3("Position", camPos);
        OglWindow->mainCamera->transform.SetPosition(camPos[0], camPos[1], camPos[2]);
        ImGui::InputFloat("Field of View", &OglWindow->mainCamera->fieldOfView);
        ImGui::InputFloat("Camera Speed", &OglWindow->mainCamera->cameraSpeed);
        ImGui::End();

        ImGui::Begin("Game Object 0");
        float goPos[] = { go.transform.GetPosition().x ,go.transform.GetPosition().y ,go.transform.GetPosition().z };
        ImGui::InputFloat3("Position", goPos);
        go.transform.Identity();
        go.transform.SetPosition(goPos[0], goPos[1], goPos[2]);
        go.transform.SetRotation(20.0f, glm::vec3(0.5f, 1.0f, 0.0f));
        go.transform.SetScale(glm::vec3(2.0f, 2.0f, 10.0f));
        ImGui::End();
        //ImGui::Begin("Rendering");
        //ImGui::Checkbox("Wireframe", &wireframe);
        //Wireframe();
        //ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        

	}
};

ActaEngine::Application* CreateApplication()
{
	return new Game();
}