#include "ActaEngine.h"
#include <limits>

using namespace ActaEngine;

class Game : public ActaEngine::Application
{
public:
    Material mat;
    Box go;


	Game() :
        mat("Shader/triangle.vert", "Shader/triangle.frag"),
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
    }


	void Update() override
	{    
        OglWindow->mainCamera->Bind(&mat);
        go.Draw(&mat);

        mat.shader->use();

        go.transform.Identity();

	}

#if defined(ACTA_DEBUG) || defined(ACTA_DEV)
    void EditorUpdate() override
    {
        // Inspector for Camera
        ImGui::Begin("Camera");

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        float camPos[] = { OglWindow->mainCamera->transform.GetPosition().x, OglWindow->mainCamera->transform.GetPosition().y, OglWindow->mainCamera->transform.GetPosition().z };
        ImGui::InputFloat3("Position", camPos);
        OglWindow->mainCamera->transform.SetPosition(camPos[0], camPos[1], camPos[2]);
        ImGui::InputFloat("Field of View", &OglWindow->mainCamera->fieldOfView);
        ImGui::InputFloat("Camera Speed", &OglWindow->mainCamera->cameraSpeed);

        ImGui::End();

        // Inspector for Game Object 0
        ImGui::Begin("Game Object 0");

        float goPos[] = { go.transform.GetPosition().x ,go.transform.GetPosition().y ,go.transform.GetPosition().z };
        float goRot[] = { go.transform.GetRotation().x , go.transform.GetRotation().y , go.transform.GetRotation().z };
        float goSca[] = { go.transform.GetScale().x , go.transform.GetScale().y , go.transform.GetScale().z };

        //ImGui::DragFloat3("Position", goPos);
        ImGui::InputFloat3("Position", goPos);
        ImGui::InputFloat3("Rotation", goRot);
        ImGui::InputFloat3("Scale", goSca);

        go.transform.Identity();
        go.transform.SetPosition(goPos[0], goPos[1], goPos[2]);
        go.transform.SetRotationEuler(goRot[0], goRot[1], goRot[2]);
        go.transform.SetScale(goSca[0], goSca[1], goSca[2]);

        ImGui::End();

    }
#endif       

};

ActaEngine::Application* CreateApplication()
{
	return new Game();
}