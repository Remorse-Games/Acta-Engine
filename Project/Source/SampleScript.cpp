#include "ActaEngine.h"

using namespace ActaEngine;

class Game : public ActaEngine::Application
{
public:
    ActaEngine::GameObject go;

    ActaEngine::Material mat;

	Game() :
        go(&mat)
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

        mat.Init();
    }


	void Update() override
	{    
        OglWindow->mainCamera->Bind(&mat);
        go.Draw(&mat);

        mat.shader->use();

        go.transform.Identity();
        go.transform.SetRotation(20.0f, glm::vec3(0.5f, 1.0f, 0.0f));

#if defined(ACTA_DEBUG) || defined(ACTA_DEV)

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
        

        ImGui::End();

        //ImGui::Begin("Rendering");
        
        //ImGui::Checkbox("Wireframe", &wireframe);
        //Wireframe();
        
        //ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif       

	}
};

ActaEngine::Application* CreateApplication()
{
	return new Game();
}