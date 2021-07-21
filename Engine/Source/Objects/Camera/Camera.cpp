#include "actapch.h"
#include "Camera.h"

extern unsigned int windowWidth;
extern unsigned int windowHeight;

bool firstMouse = true;
extern float yaw;
extern float pitch;
extern float roll;

float lastMousePosX = windowWidth / 2;
float lastMousePosY = windowHeight / 2;

Camera::Camera() :
	view(glm::mat4(0)), 
	projection(glm::mat4(0)),
	fieldOfView(45.0f),
	direction(0.0f),
	shader("Shader/triangle.vert", "Shader/triangle.frag")
{
	// Init position
	yaw = -90.0f;
	SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
}

Camera::~Camera()
{
}

void Camera::Draw()
{
	UpdateDirection();

	projection = glm::perspective(glm::radians(fieldOfView), 1280.0f / 720.0f, 0.1f, 100.0f);
	shader.SetUniformMat4("projection", projection);

	view = glm::lookAt(m_position, Forward + m_position, Up);
	shader.SetUniformMat4("view", view);
}

void Camera::Input(GLFWwindow* window)
{
	//////////////////////////////KEYBOARD CAMERA INPUT////////////////////////////////////////////

	// forward
	OpenGLInput::ProcessInputKey(window, GLFW_KEY_W, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = Forward * cameraSpeed * Time::deltaTime;
			SetPosition(m_position.x + calcSpeed.x, m_position.y + calcSpeed.y, m_position.z + calcSpeed.z);
		});
	
	// backward
	OpenGLInput::ProcessInputKey(window, GLFW_KEY_S, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = Forward * cameraSpeed * Time::deltaTime;
			SetPosition(m_position.x - calcSpeed.x, m_position.y - calcSpeed.y, m_position.z - calcSpeed.z);
		});
	
	// left
	OpenGLInput::ProcessInputKey(window, GLFW_KEY_A, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = Right * cameraSpeed * Time::deltaTime;
			SetPosition(m_position.x + calcSpeed.x, m_position.y + calcSpeed.y, m_position.z + calcSpeed.z);
		});
	
	// right
	OpenGLInput::ProcessInputKey(window, GLFW_KEY_D, GLFW_PRESS, true, [&]()
		{
			glm::vec3 calcSpeed = Right * cameraSpeed * Time::deltaTime;
			SetPosition(m_position.x - calcSpeed.x, m_position.y - calcSpeed.y, m_position.z - calcSpeed.z);
		});

	//////////////////////////////RUN CAMERA INPUT////////////////////////////////////////////
	OpenGLInput::ProcessInputKey(window, GLFW_KEY_LEFT_SHIFT, GLFW_PRESS, true, [&]()
		{
			if (!sprintInit)
			{
				cameraSpeed += cameraSprintSpeed;
				sprintInit = true;
				moveInit = false;
			}
		});

	OpenGLInput::ProcessInputKey(window, GLFW_KEY_LEFT_SHIFT, GLFW_PRESS, false, [&]()
		{
			if (!moveInit)
			{
				cameraSpeed -= cameraSprintSpeed;
				sprintInit = false;
				moveInit = true;
			}
		});

	//////////////////////////////MOUSE INPUT////////////////////////////////////////////
	OpenGLInput::ProcessInputMouse(window, GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, true, [&]()
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetCursorPosCallback(window, mouse_callback);
		});
	OpenGLInput::ProcessInputMouse(window, GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS, false, [&]()
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

	float xOffset = xPos - lastMousePosX;
	float yOffset = lastMousePosY - yPos;
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
