#pragma once
#include "Objects/Material.h"
#include "Objects/Transform.h"
#include "OpenGL/OpenGLShader.h"

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
		void UpdateDirection();
		void OnCameraMove(GLFWwindow* window, double xPos, double yPos, double& yaw, double& pitch);
	public:
		Transform transform;

	public:
		float fieldOfView;

		float nearClipping = 0.1f;
		float farClipping = 1000.0f;

		float cameraSpeed = 1.0f;
		float cameraSprintSpeed = 2.0f;

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