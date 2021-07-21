#pragma once

class Transform
{
public:
	void Identity();

	void SetPosition(const glm::vec3& pos);
	void SetPosition(const float& x, const float& y, const float& z);
	glm::vec3 GetPosition() const;
	void SetRotation(const float& angle, const glm::vec3& rot);
	glm::vec3 GetRotation() const;
	void SetScale(const glm::vec3& sca);
	glm::vec3 GetScale() const;

protected:
	void UpdateDirection();

protected:
	glm::mat4 transform;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;

	glm::vec3 Forward;
	glm::vec3 Up;
	glm::vec3 Right;
};