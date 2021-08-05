#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ActaEngine
{
	class Transform
	{
	public:
		void Identity();

		void SetPosition(const glm::vec3& pos);
		void SetPosition(const float& x, const float& y, const float& z);
		
		void SetRotation(const float& angle, const glm::vec3& rot);
		
		void SetScale(const glm::vec3& sca);
		void SetScale(const float& x, const float& y, const float& z);
		
		glm::vec3 GetPosition() const;
		
		glm::vec3 GetRotation() const;
		
		glm::vec3 GetScale() const;

		void UpdateDirection();
	public:
		glm::mat4 m_Transform;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;

		glm::vec3 Forward;
		glm::vec3 Up;
		glm::vec3 Right;

		float yaw = 0.0f;
		float pitch = 0.0f;
		float roll = 0.0f;

	public:
		//initialize with (0,0,0)
		static constexpr glm::vec3 Zero = glm::vec3(0.0f, 0.0f, 0.0f);
	};
}