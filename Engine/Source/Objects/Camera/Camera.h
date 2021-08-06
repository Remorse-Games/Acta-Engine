#pragma once
#include "Objects/Material.h"
#include "Objects/Transform.h"
#include "OpenGL/OpenGLShader.h"
#include "Core/Events/KeyEvent.h"
#include "System/Time.h"

void mouse_callback(GLFWwindow* window, double xPos, double yPos);

namespace ActaEngine
{
	class Camera
	{
	public:
		Camera();
		~Camera();

		void Draw();
		void Input(GLFWwindow* window);
		void Bind(Material* material);
		void OnCameraMove(GLFWwindow* window, double xPos, double yPos, float& yaw, float& pitch);
	public:
		Transform transform;

	public:
		float fieldOfView;
		float cameraSpeed = 1.0f;
		float cameraSprintSpeed = 2.0f;
		glm::vec3 direction;

	private:
		glm::mat4 view;
		glm::mat4 projection;

	private:
		bool sprintInit = false;
		bool moveInit = true;
		bool firstMouse = true;

		double lastMousePosX;
		double lastMousePosY;

	};
}