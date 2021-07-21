#pragma once

class Object
{
public:
	void Init();

	void SetPosition(const glm::vec3& pos);
	void SetPosition(const float& x, const float& y, const float& z);
	glm::vec3 GetPosition();
	void SetRotation(const float& angle, const glm::vec3& rot);
	glm::vec3 GetRotation();
	void SetScale(const glm::vec3& sca);
	glm::vec3 GetScale();

protected:
	void UpdateVectors();

protected:
	glm::mat4 transform;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	glm::vec3 Forward;
	glm::vec3 Up;
	glm::vec3 Right;
};