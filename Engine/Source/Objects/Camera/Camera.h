#pragma once
#include "Objects/Object.h"
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLInput.h"
#include "System/Time.h"

extern unsigned int windowWidth;
extern unsigned int windowHeight;

extern float yaw;
extern float pitch;

static float lastMousePosX = windowWidth / 2;
static float lastMousePosY = windowHeight / 2;

void mouse_callback(GLFWwindow* window, double xPos, double yPos);

class Camera : public Object
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
	Time time;

private:
	glm::mat4 view;
	glm::mat4 projection;

private:
	bool sprintInit = false;
	bool moveInit = true;

};