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


	Game() :
        box_mat("Shader/triangle.vert", "Shader/triangle.frag"),
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

        box_mat.textureGL = std::make_unique<OpenGLTexture>();
        box_mat.textureGL->push_texture("Texture/container.jpg", GL_RGB);    

        light_mat.shaderGL->use();
        light_mat.shaderGL->SetUniformVec3("objectColor", 1.0f, 0.5f, 0.31f);
        light_mat.shaderGL->SetUniformVec3("lightColor", 1.0f, 1.0f, 1.0f);

        light.transform.SetPosition(1.0f, -1.0f, 5.0f);
    }

	void Update() override
	{    
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

        box.transform.Identity();
        light.transform.Identity();
        box.transform.SetPosition(goPos[0], goPos[1], goPos[2]);
        box.transform.SetRotationEuler(goRot[0], goRot[1], goRot[2]);
        box.transform.SetScale(goSca[0], goSca[1], goSca[2]);
        light.transform.SetPosition(2.0f, -1.0f, -5.0f);

        float mixVal = box_mat.textureGL->mix;
        ImGui::SliderFloat("Mix", &mixVal, 0, 1);
        box_mat.shaderGL->SetUniformFloat("mixer", mixVal);
        box_mat.textureGL->mix = mixVal;


        ImGui::End();

    }
#endif       

};

ActaEngine::Application* CreateApplication()
{
	return new Game();
}