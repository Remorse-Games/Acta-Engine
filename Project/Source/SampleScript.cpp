#include "ActaEngine.h"

using namespace ActaEngine;

class Game : public ActaEngine::Application
{
public:
    OpenGLShader shader;
    Model model;

private:
    glm::vec3 diffuseObject = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 specularObject = glm::vec3(1.0f, 1.0f, 1.0f);
    float shininess = 32.0f;

    glm::vec3 ambientLight = glm::vec3(0.1f, 0.1f, 0.1f);
    glm::vec3 diffuseLight = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 specularLight = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 dirLightDirection = glm::vec3(-0.2f, -1.0f, -0.3f);

    float radius = 2.0f;

public:
	Game() :
        shader("Shader/object.vert", "Shader/object.frag"),
        model("Models/sponza/sponza.obj")
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
        shader.use();
        shader.SetUniformVec3("dirLight.direction", dirLightDirection);
        shader.SetUniformVec3("dirLight.ambient", diffuseLight);
        shader.SetUniformVec3("dirLight.diffuse", diffuseLight);
        shader.SetUniformVec3("dirLight.specular", specularLight);
        
        shader.SetUniformFloat("material.shininess", shininess);

        model.transform.Identity();
        model.transform.SetPosition(0.0f, 0.0f, 0.0f);
        model.transform.SetScale(1.0f, 1.0f, 1.0f);
        model.Draw(shader);
        
        OglWindow->mainCamera->Bind(&shader);
    }

#if defined(ACTA_DEBUG) || defined(ACTA_DEV)
    void EditorUpdate() override
    {
        /// Inspector for Camera
        ImGui::Begin("Camera");

        float camPos[] = { OglWindow->mainCamera->transform.GetPosition().x, OglWindow->mainCamera->transform.GetPosition().y, OglWindow->mainCamera->transform.GetPosition().z };

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::InputFloat3("Position", camPos);
        OglWindow->mainCamera->transform.SetPosition(camPos[0], camPos[1], camPos[2]);
        ImGui::InputFloat("Field of View", &OglWindow->mainCamera->fieldOfView);
        ImGui::InputFloat("Camera Speed", &OglWindow->mainCamera->cameraSpeed);
        ImGui::InputFloat("Near", &OglWindow->mainCamera->nearClipping);
        ImGui::InputFloat("Far", &OglWindow->mainCamera->farClipping);
        ImGui::End();

        // Inspector for Game Object 0
        ImGui::Begin("Game Object 0");
        
        float modelPos[] = { model.transform.GetPosition().x, model.transform.GetPosition().y, model.transform.GetPosition().z };

        // transform etc
        ImGui::InputFloat3("Position", modelPos);

        model.transform.SetPosition(modelPos[0], modelPos[1], modelPos[2]);

        // light and material stuff
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

        float dirL[] = { dirLightDirection.x, dirLightDirection.y, dirLightDirection.z };
        float diffL[] = { diffuseLight.x, diffuseLight.y, diffuseLight.z };

        ImGui::DragFloat3("Light Direction", dirL);
        ImGui::ColorPicker4("Light Color", diffL);

        dirLightDirection = glm::vec3(dirL[0], dirL[1], dirL[2]);
        diffuseLight = glm::vec3(diffL[0], diffL[1], diffL[2]);

        ImGui::End();

    }
#endif       

};

ActaEngine::Application* CreateApplication()
{
	return new Game();
}