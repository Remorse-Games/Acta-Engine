#include "ActaEngine.h"

using namespace ActaEngine;

class Game : public ActaEngine::Application
{
public:
    //OpenGLShader* shader;
    //Camera mainCamera;

    ActaEngine::GameObject go;
    ActaEngine::GameObject go1;

    //std::vector<ActaEngine::GameObject> gameObject;
    //std::vector<glm::vec3> cubePositions;
    //std::vector<float> objectPosition;

	Game()
	{
		spdlog::info("Start the game!");
        go.transform.Identity();
        go.transform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
        go.transform.SetRotation(20.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    }

	~Game()
	{
        //delete shader;
	}

	void Start() override
	{
        //gameObject.reserve(10);

        //for (int i = 0; i < 10; i++)
        //{
        //    gameObject.push_back(go);
        //}

        //for (int i = 0; i < 3; i++)
        //{
        //    objectPosition.push_back(0.0f);
        //}

        //cubePositions = {
        //glm::vec3(0.0f,  0.0f,  0.0f),
        //glm::vec3(2.0f,  5.0f, -15.0f),
        //glm::vec3(-1.5f, -2.2f, -2.5f),
        //glm::vec3(-3.8f, -2.0f, -12.3f),
        //glm::vec3(2.4f, -0.4f, -3.5f),
        //glm::vec3(-1.7f,  3.0f, -7.5f),
        //glm::vec3(1.3f, -2.0f, -2.5f),
        //glm::vec3(1.5f,  2.0f, -2.5f),
        //glm::vec3(1.5f,  0.2f, -1.5f),
        //glm::vec3(-1.3f,  1.0f, -1.5f)
        //};

        //shader = new OpenGLShader("Shader/triangle.vert", "Shader/triangle.frag");

	}

	//TODO: not updating yet
	void Update() override
	{
        //mainCamera.Draw();

        //for (int i = 1; i < 10; i++)
        //{
        //    gameObject[i].Identity();
        //    gameObject[i].SetPosition(cubePositions[i]);
        //    float angle = 20.0f * i;
        //    gameObject[i].SetRotation(angle, glm::vec3(0.5f, 1.0f, 0.0f));
        //    gameObject[i].Draw();
        //}

        // //Don't forget to use Init, or matrix won't reset and cause problem.
        //gameObject[0].Identity();
        //gameObject[0].SetPosition(glm::vec3(objectPosition[0], objectPosition[1], objectPosition[2]));
        //gameObject[0].SetScale(glm::vec3(0.5f, 0.5f, 0.5f));
        //gameObject[0].Draw();
        go.Draw();

       // spdlog::info(go.transform.m_Transform[0][0]);

        //go1.transform.Identity();
        //go1.transform.SetPosition(glm::vec3(2.0f, 1.0f, 2.0f));
        //go1.transform.SetRotation(20.0f, glm::vec3(0.5f, 1.0f, 0.0f));
       // go1.Draw();

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
        spdlog::info(goPos[0]);
        ImGui::InputFloat3("Position", goPos);
        go.transform.SetPosition(goPos[0], goPos[1], goPos[2]);
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