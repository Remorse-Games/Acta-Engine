#include "actapch.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Camera.h"

#include "Objects/Transform.h"
#include "OpenGL/OpenGLShader.h"
#include "Core/Events/MouseEvent.h"
#include "Core/Events/KeyEvent.h"
#include "System/Time.h"
#include "Objects/Material.h"

extern unsigned int windowWidth;
extern unsigned int windowHeight;

bool firstMouse = true;
extern float yaw;
extern float pitch;
extern float roll;

double lastMousePosX = double(windowWidth / 2);
double lastMousePosY = double(windowHeight / 2);

ActaEngine::Camera::Camera() :
	view(glm::mat4(0)), 
	projection(glm::mat4(0)),
	fieldOfView(45.0f),
	direction(0.0f)
{
	// Init position
	yaw = -90.0f;
	transform.SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
}

ActaEngine::Camera::~Camera()
{
}

void ActaEngine::Camera::Draw()
{
	transform.UpdateDirection();

	projection = glm::perspective(glm::radians(fieldOfView), 1280.0f / 720.0f, 0.1f, 100.0f);
	view = glm::lookAt(transform.m_position, transform.Forward + transform.m_position, transform.Up);
}

void ActaEngine::Camera::Bind(Material* material)
{
	material->shader->SetUniformMat4("projection", projection);
	material->shader->SetUniformMat4("view", view);
}

void ActaEngine::Camera::Input(GLFWwindow* window)
{
	//////////////////////////////KEYBOARD CAMERA INPUT////////////////////////////////////////////

	// forward
	KeyEvent::ProcessInputKey(window, GLFW_KEY_W, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = transform.Forward * cameraSpeed * Time::deltaTime;
			transform.SetPosition(transform.m_position.x + calcSpeed.x, transform.m_position.y + calcSpeed.y, transform.m_position.z + calcSpeed.z);
		});
	
	// backward
	KeyEvent::ProcessInputKey(window, GLFW_KEY_S, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = transform.Forward * cameraSpeed * Time::deltaTime;
			transform.SetPosition(transform.m_position.x - calcSpeed.x, transform.m_position.y - calcSpeed.y, transform.m_position.z - calcSpeed.z);
		});
	
	// left
	KeyEvent::ProcessInputKey(window, GLFW_KEY_A, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = transform.Right * cameraSpeed * Time::deltaTime;

			transform.SetPosition(transform.m_position.x + calcSpeed.x, transform.m_position.y + calcSpeed.y, transform.m_position.z + calcSpeed.z);
		});
	
	// right
	KeyEvent::ProcessInputKey(window, GLFW_KEY_D, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = transform.Right * cameraSpeed * Time::deltaTime;
			transform.SetPosition(transform.m_position.x - calcSpeed.x, transform.m_position.y - calcSpeed.y, transform.m_position.z - calcSpeed.z);
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
			glfwSetCursorPosCallback(window, mouse_callback);
		});
	MouseEvent::ProcessInputMouse(window, GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, false, [&]()
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) { firstMouse = true; });
		});

}


void mouse_callback(GLFWwindow* window, double xPos, double yPos)
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
