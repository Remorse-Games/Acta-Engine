#include "actapch.h"
#include "Camera.h"

Camera::Camera() :
	view(glm::mat4(0)), 
	projection(glm::mat4(0)),
	fieldOfView(45.0f), 
	shader("Shader/triangle.vert", "Shader/triangle.frag")
{
	// Init position
	Init();
	SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
}

Camera::~Camera()
{
}

void Camera::Draw()
{
	time.Update();
	
	UpdateVectors();

	projection = glm::perspective(glm::radians(fieldOfView), 1280.0f / 720.0f, 0.1f, 100.0f);
	shader.SetUniformMat4("projection", projection);

	view = glm::lookAt(position, Forward + position, Up);
	shader.SetUniformMat4("view", view);
}


void Camera::Input(GLFWwindow* window)
{
	// forward
	OpenGLInput::ProcessInput(window, GLFW_KEY_W, GLFW_PRESS, [&]()
		{
			glm::vec3 calcSpeed = Forward * cameraSpeed * time.deltaTime;
			SetPosition(position.x + calcSpeed.x, position.y + calcSpeed.y, position.z + calcSpeed.z);
		});
	
	// backward
	OpenGLInput::ProcessInput(window, GLFW_KEY_S, GLFW_PRESS, [&]()
		{
			glm::vec3 calcSpeed = Forward * cameraSpeed * time.deltaTime;
			SetPosition(position.x - calcSpeed.x, position.y - calcSpeed.y, position.z - calcSpeed.z);
		});
	
	// left
	OpenGLInput::ProcessInput(window, GLFW_KEY_A, GLFW_PRESS, [&]()
		{
			glm::vec3 calcSpeed = Right * cameraSpeed * time.deltaTime;
			SetPosition(position.x + calcSpeed.x, position.y + calcSpeed.y, position.z + calcSpeed.z);
		});
	
	// right
	OpenGLInput::ProcessInput(window, GLFW_KEY_D, GLFW_PRESS, [&]()
		{
			glm::vec3 calcSpeed = Right * cameraSpeed * time.deltaTime;
			SetPosition(position.x - calcSpeed.x, position.y - calcSpeed.y, position.z - calcSpeed.z);
		});

	OpenGLInput::ProcessInput(window, GLFW_KEY_LEFT_SHIFT, GLFW_PRESS, true, [&]()
		{
			if (!sprintInit)
			{
				cameraSpeed += cameraSprintSpeed;
				sprintInit = true;
				moveInit = false;
			}
		});

	OpenGLInput::ProcessInput(window, GLFW_KEY_LEFT_SHIFT, GLFW_PRESS, false, [&]()
		{
			if (!moveInit)
			{
				cameraSpeed -= cameraSprintSpeed;
				sprintInit = false;
				moveInit = true;
			}
		});

}