#include "ActaEngine.h"
#include <limits>

using namespace ActaEngine;

class Game : public ActaEngine::Application
{
public:
    Material material;
    Model model;
private:
    glm::vec3 diffuseObject = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 specularObject = glm::vec3(1.0f, 1.0f, 1.0f);
    float shininess = 32.0f;

    glm::vec3 ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);
    glm::vec3 diffuseLight = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 specularLight = glm::vec3(1.0f, 1.0f, 1.0f);

    float radius = 2.0f;

public:
	Game() :
        material("Shader/object.vert", "Shader/object.frag"),
        model("Models/backpack/backpack.obj")
	{
        Start();
    }

	~Game()
	{
    }

	void Start() override
	{
        spdlog::info("Start the game!");           
    }

	void Update() override
	{   
      //  model.Draw(material);
        OglWindow->mainCamera->Bind(&material);
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
        
        float diff[] = { diffuseObject.x, diffuseObject.y, diffuseObject.z };
        float spec[] = { specularObject.x, specularObject.y, specularObject.z };

        ImGui::ColorPicker4("Diffuse", diff);
        ImGui::SliderFloat3("Specular", spec, 0.0f, 1.0f);

        diffuseObject = glm::vec3(diff[0], diff[1], diff[2]);
        specularObject = glm::vec3(spec[0], spec[1], spec[2]);

        ImGui::SliderFloat("shininess", &shininess, 2, 256);
        ImGui::SliderFloat("Light Distance", &radius, 1, 50);
        ImGui::End();


        ImGui::Begin("Directional Light");

        float diffL[] = { diffuseLight.x, diffuseLight.y, diffuseLight.z };
        float specL[] = { specularLight.x, specularLight.y, specularLight.z };

        ImGui::ColorPicker4("Diffuse", diffL);
        ImGui::SliderFloat3("Specular", specL, 0.0f, 1.0f);

        diffuseLight = glm::vec3(diffL[0], diffL[1], diffL[2]);
        specularLight = glm::vec3(specL[0], specL[1], specL[2]);

        ImGui::End();

    }
#endif       

};

ActaEngine::Application* CreateApplication()
{
	return new Game();
}