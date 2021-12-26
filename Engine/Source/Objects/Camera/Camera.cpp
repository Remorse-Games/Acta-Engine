#include "actapch.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Camera.h"

#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"
#include "System/Time.h"
#include "Objects/Material.h"

extern unsigned int windowWidth;
extern unsigned int windowHeight;

ActaEngine::Camera::Camera() :
	view(glm::mat4(0)), 
	projection(glm::mat4(0)),
	fieldOfView(45.0f),
	lastMousePosX(windowWidth / 2),
	lastMousePosY(windowHeight / 2)
{
	// Init position
	transform.yaw = -90.0f;
	transform.SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
}

ActaEngine::Camera::~Camera()
{
}

void ActaEngine::Camera::Draw()
{
	UpdateDirection();

	projection = glm::perspective(glm::radians(fieldOfView), (float)windowWidth / (float)windowHeight, nearClipping, farClipping);
	//projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, nearClipping, farClipping);
	view = glm::lookAt(transform.GetPosition(), transform.forward + transform.GetPosition(), transform.up);
}

void ActaEngine::Camera::Bind(Material* material)
{
	material->shaderGL->SetUniformMat4("projection", projection);
	material->shaderGL->SetUniformMat4("view", view);
}

void ActaEngine::Camera::UpdateDirection()
{
	// need implementing roll later
	transform.direction.x = (float)cos(glm::radians(transform.yaw)) * cos(glm::radians(transform.pitch));
	transform.direction.y = (float)sin(glm::radians(transform.pitch));
	transform.direction.z = (float)sin(glm::radians(transform.yaw)) * cos(glm::radians(transform.pitch));

	transform.forward = glm::normalize(transform.direction);
	transform.right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), transform.forward));
	transform.up = glm::cross(transform.forward, transform.right);
}


void ActaEngine::Camera::Input(GLFWwindow* window)
{
	//////////////////////////////KEYBOARD CAMERA INPUT////////////////////////////////////////////

	// forward
	KeyEvent::ProcessInputKey(window, GLFW_KEY_W, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = transform.forward * cameraSpeed * Time::deltaTime;
			transform.SetPosition(transform.GetPosition().x + calcSpeed.x, transform.GetPosition().y + calcSpeed.y, transform.GetPosition().z + calcSpeed.z);
		});
	
	// backward
	KeyEvent::ProcessInputKey(window, GLFW_KEY_S, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = transform.forward * cameraSpeed * Time::deltaTime;
			transform.SetPosition(transform.GetPosition().x - calcSpeed.x, transform.GetPosition().y - calcSpeed.y, transform.GetPosition().z - calcSpeed.z);
		});
	
	// left
	KeyEvent::ProcessInputKey(window, GLFW_KEY_A, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = transform.right * cameraSpeed * Time::deltaTime;
			transform.SetPosition(transform.GetPosition().x + calcSpeed.x, transform.GetPosition().y + calcSpeed.y, transform.GetPosition().z + calcSpeed.z);
		});
	
	// right
	KeyEvent::ProcessInputKey(window, GLFW_KEY_D, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = transform.right * cameraSpeed * Time::deltaTime;
			transform.SetPosition(transform.GetPosition().x - calcSpeed.x, transform.GetPosition().y - calcSpeed.y, transform.GetPosition().z - calcSpeed.z);
		});

	//////////////////////////////RUN CAMERA INPUT////////////////////////////////////////////
	KeyEvent::ProcessInputKey(window, GLFW_KEY_LEFT_SHIFT, GLFW_PRESS, true, [&]()
		{
			if (!sprintInit)
			{
				cameraSpeed += cameraSprintSpeed;
				sprintInit = true;
				moveInit = false;
			}
		});

	KeyEvent::ProcessInputKey(window, GLFW_KEY_LEFT_SHIFT, GLFW_PRESS, false, [&]()
		{
			if (!moveInit)
			{
				cameraSpeed -= cameraSprintSpeed;
				sprintInit = false;
				moveInit = true;
			}
		});

	//////////////////////////////MOUSE INPUT////////////////////////////////////////////
	MouseEvent::ProcessInputMouse(window, GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, true, [&]()
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
				{
 					Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
					camera->OnCameraMove(window, xPos, yPos, camera->transform.yaw, camera->transform.pitch);
				});
		});
	MouseEvent::ProcessInputMouse(window, GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, false, [&]()
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) 
				{ 
					Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
					camera->firstMouse = true; 
				});
		});

}

 void ActaEngine::Camera::OnCameraMove(GLFWwindow* window, double xPos, double yPos, double& yaw, double& pitch)
{
	if (firstMouse)
	{
		lastMousePosX = xPos;
		lastMousePosY = yPos;
		firstMouse = false;
	}

	double xOffset = xPos - lastMousePosX;
	double yOffset = lastMousePosY - yPos;
	lastMousePosX = xPos;
	lastMousePosY = yPos;

	const float mouseSensitivity = 0.1f;
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	yaw += xOffset;
	pitch += yOffset;
	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	else if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}
}
