#include "ActaEngine.h"
#include <limits>

using namespace ActaEngine;

class Game : public ActaEngine::Application
{
public:
    Material box_mat;
    Material light_mat;
    Box box;
    Box light;

private:
    glm::vec3 ambientObject = glm::vec3(0.1f, 0.0f, 1.0f);
    glm::vec3 diffuseObject = glm::vec3(0.5f, 0.0f, 1.0f);
    glm::vec3 specularObject = glm::vec3(0.5f, 0.0f, 1.0f);
    float shininess = 32.0f;

    glm::vec3 ambientLight = glm::vec3(0.1f, 0.0f, 1.0f);
    glm::vec3 diffuseLight = glm::vec3(0.5f, 0.0f, 1.0f);
    glm::vec3 specularLight = glm::vec3(0.5f, 0.0f, 1.0f);

    float radius = 2.0f;

public:
	Game() :
        box_mat("Shader/object.vert", "Shader/object.frag"),
        light_mat("Shader/lighting.vert", "Shader/lighting.frag"),
        box(box_mat, "Box"),
        light(light_mat, "Light")
	{
        Start();
    }

	~Game()
	{

    }

	void Start() override
	{
        spdlog::info("Start the game!");     

        //box_mat.textureGL = std::make_unique<OpenGLTexture>();
        //box_mat.textureGL->push_texture("Texture/container.jpg", GL_RGB);    
    }

	void Update() override
	{

        box.transform.Identity();
        light.transform.Identity();

        // box pos
        box.transform.SetPosition(0.0f, 0.0f, 0.0f);

        // rotate the cube box
        float lightx = sin(glfwGetTime() / 8.0f) * radius;
        float lightz = cos(glfwGetTime() / 8.0f) * radius;

        // light pos
        light.transform.SetPosition(lightx, 0.0f, lightz);

        box_mat.shaderGL->use();
        box_mat.shaderGL->SetUniformVec3("lightPos", light.transform.GetPosition());
        box_mat.shaderGL->SetUniformVec3("viewPos", OglWindow->mainCamera->transform.GetPosition());

        box_mat.shaderGL->SetUniformVec3("material.ambient", ambientObject);
        box_mat.shaderGL->SetUniformVec3("material.diffuse", diffuseObject);
        box_mat.shaderGL->SetUniformVec3("material.specular", specularObject);
        box_mat.shaderGL->SetUniformFloat("material.shininess", shininess);

        box_mat.shaderGL->SetUniformVec3("light.ambient", ambientLight);
        box_mat.shaderGL->SetUniformVec3("light.diffuse", diffuseLight);
        box_mat.shaderGL->SetUniformVec3("light.specular", specularLight);

        light_mat.shaderGL->use();
        light_mat.shaderGL->SetUniformVec3("lightColor", ambientLight);

        box.Draw(box_mat);
        light.Draw(light_mat);

        //TODO: if box binded first, the 2nd texture will be missing.
        //make sure if we want to reproduce this problem we need activate the 2nd object with 2 texture.

        OglWindow->mainCamera->Bind(&light_mat);
        OglWindow->mainCamera->Bind(&box_mat);


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

        float goPos[] = { box.transform.GetPosition().x ,box.transform.GetPosition().y ,box.transform.GetPosition().z };
        float goRot[] = { box.transform.GetRotation().x , box.transform.GetRotation().y , box.transform.GetRotation().z };
        float goSca[] = { box.transform.GetScale().x , box.transform.GetScale().y , box.transform.GetScale().z };

        //ImGui::DragFloat3("Position", goPos);
        ImGui::InputFloat3("Position", goPos);
        ImGui::InputFloat3("Rotation", goRot);
        ImGui::InputFloat3("Scale", goSca);
        
        box.transform.SetPosition(goPos[0], goPos[1], goPos[2]);
        box.transform.SetRotationEuler(goRot[0], goRot[1], goRot[2]);
        box.transform.SetScale(goSca[0], goSca[1], goSca[2]);

        //float mixVal = box_mat.textureGL->mix;
        //ImGui::SliderFloat("Mix", &mixVal, 0, 1);
        //box_mat.shaderGL->SetUniformFloat("mixer", mixVal);
        //box_mat.textureGL->mix = mixVal;
        
        float amb[] = { ambientObject.x, ambientObject.y, ambientObject.z, 0.0f };
        float diff[] = { diffuseObject.x, diffuseObject.y, diffuseObject.z };
        float spec[] = { specularObject.x, specularObject.y, specularObject.z };

        ImGui::ColorPicker4("Ambient", amb);
        ImGui::ColorPicker4("Diffuse", diff);
        //ImGui::SliderFloat3("Diffuse", diff, 0.0f, 1.0f);
        ImGui::SliderFloat3("Specular", spec, 0.0f, 1.0f);

        ambientObject = glm::vec3(amb[0], amb[1], amb[2]);
        diffuseObject = glm::vec3(diff[0], diff[1], diff[2]);
        specularObject = glm::vec3(spec[0], spec[1], spec[2]);

        ImGui::SliderFloat("shininess", &shininess, 2, 256);
        ImGui::SliderFloat("Light Distance", &radius, 1, 50);
        ImGui::End();


        ImGui::Begin("Directional Light");

        float ambL[] = { ambientLight.x, ambientLight.y, ambientLight.z, 0.0f };
        float diffL[] = { diffuseLight.x, diffuseLight.y, diffuseLight.z };
        float specL[] = { specularLight.x, specularLight.y, specularLight.z };

        ImGui::ColorPicker4("Ambient", ambL);
        ImGui::ColorPicker4("Diffuse", diffL);
       // ImGui::SliderFloat3("Diffuse", diffL, 0.0f, 1.0f);
        ImGui::SliderFloat3("Specular", specL, 0.0f, 1.0f);

        ambientLight = glm::vec3(ambL[0], ambL[1], ambL[2]);
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