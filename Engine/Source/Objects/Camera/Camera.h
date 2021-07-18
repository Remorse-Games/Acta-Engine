#pragma once
#include "Objects/Object.h"
#include "OpenGL/OpenGLShader.h"
#include "OpenGL/OpenGLInput.h"
#include "System/Time.h"

extern float yaw;
extern float pitch;

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
	glm::vec3 direction;

private:
	OpenGLShader shader;
	Time time;

private:
	glm::mat4 view;
	glm::mat4 projection;

	glm::vec3 cameraTarget;
	
	glm::vec3 cameraForward;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

};