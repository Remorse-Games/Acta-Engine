#include "ActaEngine.h"
#include <limits>

using namespace ActaEngine;

class Game : public ActaEngine::Application
{
public:
    Material box_mat;
    std::vector<Box*> multiBox {
        new Box(box_mat, "Box multi"),
        new Box(box_mat, "Box multi"),
        new Box(box_mat, "Box multi"),
        new Box(box_mat, "Box multi"),
        new Box(box_mat, "Box multi"),
        new Box(box_mat, "Box multi"),
        new Box(box_mat, "Box multi"),
        new Box(box_mat, "Box multi"),
        new Box(box_mat, "Box multi"),
        new Box(box_mat, "Box multi"),
    };
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
        box_mat("Shader/object.vert", "Shader/object.frag")       
	{
        Start();
    }

	~Game()
	{
        for (Box* b : multiBox)
        {
            delete b;
        }
    }

	void Start() override
	{
        spdlog::info("Start the game!");           

        box_mat.textureGL = std::make_unique<OpenGLTexture>();
        box_mat.textureGL->push_texture("Texture/container2.png", GL_RGBA);
        box_mat.textureGL->push_texture("Texture/container2_specular.png", GL_RGBA);
    }

	void Update() override
	{        
        // rotate the cube box
        //float lightx = sin(glfwGetTime() / 8.0f) * radius;
        //float lightz = cos(glfwGetTime() / 8.0f) * radius;

        // light pos
        //light.transform.SetPosition(lightx, 0.0f, lightz);

        box_mat.shaderGL->use();

        // positions of the point lights
        glm::vec3 pointLightPositions[] = {
            glm::vec3(0.7f,  0.2f,  2.0f),
            glm::vec3(2.3f, -3.3f, -4.0f),
            glm::vec3(-4.0f,  2.0f, -12.0f),
            glm::vec3(0.0f,  0.0f, -3.0f)
        };

        // directional light
        box_mat.shaderGL->SetUniformVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        box_mat.shaderGL->SetUniformVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        box_mat.shaderGL->SetUniformVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        box_mat.shaderGL->SetUniformVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        box_mat.shaderGL->SetUniformVec3("pointLights[0].position", pointLightPositions[0]);
        box_mat.shaderGL->SetUniformVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        box_mat.shaderGL->SetUniformVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        box_mat.shaderGL->SetUniformVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        box_mat.shaderGL->SetUniformFloat("pointLights[0].constant", 1.0f);
        box_mat.shaderGL->SetUniformFloat("pointLights[0].linear", 0.09f);
        box_mat.shaderGL->SetUniformFloat("pointLights[0].quadratic", 0.032f);
        // point light 2
        box_mat.shaderGL->SetUniformVec3("pointLights[1].position", pointLightPositions[1]);
        box_mat.shaderGL->SetUniformVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        box_mat.shaderGL->SetUniformVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        box_mat.shaderGL->SetUniformVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        box_mat.shaderGL->SetUniformFloat("pointLights[1].constant", 1.0f);
        box_mat.shaderGL->SetUniformFloat("pointLights[1].linear", 0.09f);
        box_mat.shaderGL->SetUniformFloat("pointLights[1].quadratic", 0.032f);
        // point light 3
        box_mat.shaderGL->SetUniformVec3("pointLights[2].position", pointLightPositions[2]);
        box_mat.shaderGL->SetUniformVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        box_mat.shaderGL->SetUniformVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        box_mat.shaderGL->SetUniformVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        box_mat.shaderGL->SetUniformFloat("pointLights[2].constant", 1.0f);
        box_mat.shaderGL->SetUniformFloat("pointLights[2].linear", 0.09f);
        box_mat.shaderGL->SetUniformFloat("pointLights[2].quadratic", 0.032f);
        //// point light 4
        box_mat.shaderGL->SetUniformVec3("pointLights[0].position", pointLightPositions[0]);
        box_mat.shaderGL->SetUniformVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        box_mat.shaderGL->SetUniformVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        box_mat.shaderGL->SetUniformVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        box_mat.shaderGL->SetUniformFloat("pointLights[0].constant", 1.0f);
        box_mat.shaderGL->SetUniformFloat("pointLights[0].linear", 0.09f);
        box_mat.shaderGL->SetUniformFloat("pointLights[0].quadratic", 0.032f);
        // spotLight
        box_mat.shaderGL->SetUniformVec3("spotLight.position", OglWindow->mainCamera->transform.GetPosition());
        box_mat.shaderGL->SetUniformVec3("spotLight.direction", OglWindow->mainCamera->transform.forward);
        box_mat.shaderGL->SetUniformVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        box_mat.shaderGL->SetUniformVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        box_mat.shaderGL->SetUniformVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        box_mat.shaderGL->SetUniformFloat("spotLight.constant", 1.0f);
        box_mat.shaderGL->SetUniformFloat("spotLight.linear", 0.09f);
        box_mat.shaderGL->SetUniformFloat("spotLight.quadratic", 0.032f);
        box_mat.shaderGL->SetUniformFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        box_mat.shaderGL->SetUniformFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

        box_mat.shaderGL->SetUniformVec3("viewPos", OglWindow->mainCamera->transform.GetPosition());
        box_mat.shaderGL->SetUniformFloat("material.shininess", shininess);

        glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
        };

        for (unsigned int i = 0; i < 10; i++)
        {
            float angle = 20.0f * i;
            
            multiBox[i]->transform.Identity();

            multiBox[i]->transform.SetPosition(cubePositions[i]);
            //boxi.transform.SetRotation(glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            multiBox[i]->transform.SetRotationEuler(angle, 0.0f, 1.0f);
            multiBox[i]->Draw(box_mat);
        }

        //for (unsigned int i = 0; i < 10; i++)
        //{
        //    boxes[i].Draw(box_mat);
        //}

        //TODO: if box binded first, the 2nd texture will be missing.
        //make sure if we want to reproduce this problem we need activate the 2nd object with 2 texture.

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

        //float goPos[] = { box.transform.GetPosition().x ,box.transform.GetPosition().y ,box.transform.GetPosition().z };
       // float goRot[] = { box.transform.GetRotation().x , box.transform.GetRotation().y , box.transform.GetRotation().z };
        //float goSca[] = { box.transform.GetScale().x , box.transform.GetScale().y , box.transform.GetScale().z };

        //ImGui::DragFloat3("Position", goPos);
      //  ImGui::InputFloat3("Position", goPos);
       // ImGui::InputFloat3("Rotation", goRot);
      //  ImGui::InputFloat3("Scale", goSca);
        
      //  box.transform.SetPosition(goPos[0], goPos[1], goPos[2]);
     //   box.transform.SetRotationEuler(goRot[0], goRot[1], goRot[2]);
      //  box.transform.SetScale(goSca[0], goSca[1], goSca[2]);

        //float mixVal = box_mat.textureGL->mix;
        //ImGui::SliderFloat("Mix", &mixVal, 0, 1);
        //box_mat.shaderGL->SetUniformFloat("mixer", mixVal);
        //box_mat.textureGL->mix = mixVal;
        
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