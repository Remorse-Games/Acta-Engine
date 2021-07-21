#pragma once
#include "Objects/Transform.h"
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLInput.h"
#include "System/Time.h"

void mouse_callback(GLFWwindow* window, double xPos, double yPos);

class Camera : public Transform
{
public:
	Camera();
	~Camera();

	void Draw();
	void Input(GLFWwindow* window);

public:
	float fieldOfView;
	float cameraSpeed = 1.0f;
	float cameraSprintSpeed = 2.0f;
	glm::vec3 direction;

private:
	OpenGLShader shader;

private:
	glm::mat4 view;
	glm::mat4 projection;

private:
	bool sprintInit = false;
	bool moveInit = true;

};