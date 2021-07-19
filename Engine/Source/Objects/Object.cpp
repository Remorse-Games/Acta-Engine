#include "actapch.h"
#include "Object.h"

extern float yaw;
extern float pitch;

void Object::Init()
{
	transform = glm::mat4(1.0f);
}

void Object::SetPosition(const glm::vec3& pos)
{
	position = pos;
	transform = glm::translate(transform, position);
}

void Object::SetPosition(const float& x, const float& y, const float& z)
{
	position = glm::vec3(x, y, z);
	transform = glm::translate(transform, position);
}

glm::vec3 Object::GetPosition()
{
	return position;
}

void Object::SetRotation(const float& angle, const glm::vec3& rot)
{
	rotation = rot;
	transform = glm::rotate(transform, glm::radians(angle), rotation);
}

glm::vec3 Object::GetRotation()
{
	return rotation;
}

void Object::SetScale()
{
}

glm::vec3 Object::GetScale()
{
	return scale;
}

void Object::UpdateVectors()
{
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	Forward = glm::normalize(direction);
	Right = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), Forward));
	Up = glm::cross(Forward, Right);

}
