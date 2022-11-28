#include "ActaEngine.h"

using namespace ActaEngine;

class Game : public ActaEngine::Application
{
public:
    OpenGLShader shader;
    OpenGLShader cubeShader;
    OpenGLShader stencilShader;

    Model guitar;
    Model cube;
    Model cubeStencilTest;
    Model cubeStencilTest1;
    Model cube1;
    Model cube2;

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
        cubeShader("Shader/object.vert", "Shader/object.frag"),
        stencilShader("Shader/stencil_single_color.vert", "Shader/stencil_single_color.frag"),
        guitar("Models/backpack/backpack.obj"),
        cube("Models/cube/cube.obj"),
        cubeStencilTest("Models/cube/cube.obj"),
        cubeStencilTest1("Models/cube/cube.obj"),
        cube1("Models/cube/cube.obj"),
        cube2("Models/cube/cube.obj")
    {
        Start();
    }

	~Game()
	{
    }

	void Start() override
	{
        spdlog::info("Start the game!");
        diffuseLight = glm::vec3(0.5f);
        guitar.transform.SetPosition(25.0f, 0.0f, 0.0f);
    }

	void Update() override
	{   
        //---START OF SHADER SETUP
        // guitar shader
        shader.use();
        shader.SetUniformVec3("dirLight.direction", dirLightDirection);
        shader.SetUniformVec3("dirLight.ambient", diffuseLight);
        shader.SetUniformVec3("dirLight.diffuse", diffuseLight);
        shader.SetUniformVec3("dirLight.specular", specularLight);
        
        shader.SetUniformFloat("material.shininess", shininess);

        shader.SetUniformVec3("viewPos", OglWindow->mainCamera->transform.GetPosition());

        cubeShader.SetUniformVec3("dirLight.direction", dirLightDirection);
        cubeShader.SetUniformVec3("dirLight.ambient", diffuseLight);
        cubeShader.SetUniformVec3("dirLight.diffuse", diffuseLight);
        cubeShader.SetUniformVec3("dirLight.specular", specularLight);

        cubeShader.SetUniformFloat("material.shininess", shininess);

        cubeShader.SetUniformVec3("viewPos", OglWindow->mainCamera->transform.GetPosition());
        //---END OF SHADER SETUP

        glStencilMask(0x00);

        // guitar object
        guitar.Draw(shader);

        // floor
        cube2.Draw(shader);
        cube2.transform.Identity();
        cube2.transform.SetPosition(0.0f, -3.0f, 0.0f);
        cube2.transform.SetScale(15.0f, 5.0f, 15.0f);

        cubeShader.use();

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        // front box
        cube.Draw(shader);
        cube.transform.Identity();
        cube.transform.SetPosition(0.0f, 0.0f, 0.0f);

        // back box
        cube1.Draw(shader);
        cube1.transform.Identity();
        cube1.transform.SetPosition(3.0f, 0.0f, -5.0f);


        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        stencilShader.use();
        cubeStencilTest.Draw(stencilShader);
        cubeStencilTest.transform.Identity();
        cubeStencilTest.transform.SetPosition(0.0f, 0.0f, 0.0f);
        cubeStencilTest.transform.SetScale(1.1f, 1.1f, 1.1f);

        cubeStencilTest1.Draw(stencilShader);
        cubeStencilTest1.transform.Identity();
        cubeStencilTest1.transform.SetPosition(3.0f, 0.0f, -5.0f);
        cubeStencilTest1.transform.SetScale(1.1f, 1.1f, 1.1f);
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);

        // camera binding to shader
        OglWindow->mainCamera->Bind(&shader);
        OglWindow->mainCamera->Bind(&cubeShader);
        OglWindow->mainCamera->Bind(&stencilShader);
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
        
        float modelPos[] = { guitar.transform.GetPosition().x, guitar.transform.GetPosition().y, guitar.transform.GetPosition().z };
        float modelRot[] = { guitar.transform.GetRotation().x, guitar.transform.GetRotation().y, guitar.transform.GetRotation().z };
        float modelSca[] = { guitar.transform.GetScale().x, guitar.transform.GetScale().y, guitar.transform.GetScale().z };

        ImGui::Text("Vertices %d", guitar.verticesCount);
        ImGui::Text("Mesh %d", guitar.meshCount);

        // transform etc
        ImGui::InputFloat3("Position", modelPos);
        ImGui::DragFloat3("Rotation", modelRot);
        ImGui::InputFloat3("Scale", modelSca);

        guitar.transform.Identity();
        guitar.transform.SetScale(1.0f, 1.0f, 1.0f);
        guitar.transform.SetPosition(modelPos[0], modelPos[1], modelPos[2]);
        guitar.transform.SetRotationEuler(modelRot[0], modelRot[1], modelRot[2]);
        guitar.transform.SetScale(modelSca[0], modelSca[1], modelSca[2]);

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
        float diffL[] = { diffuseLight.x, diffuseLight.y, diffuseLight.z};

        ImGui::DragFloat3("Light Direction", dirL);
        ImGui::ColorPicker3("Light Color", diffL);

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