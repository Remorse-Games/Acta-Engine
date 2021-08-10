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
		void SetRotationEuler(const glm::vec3& rot);
		void SetRotationEuler(const float& x, const float& y, const float& z);

		void SetScale(const glm::vec3& sca);
		void SetScale(const float& x, const float& y, const float& z);
		
		glm::vec3 GetPosition() const;
		
		glm::vec3 GetRotation() const;
		
		glm::vec3 GetScale() const;

	public:
		glm::mat4 m_Transform;

		glm::vec3 m_position;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;

		glm::vec3 Forward;
		glm::vec3 Up;
		glm::vec3 Right;

		glm::vec3 direction;

		double yaw = 0.0;
		double pitch = 0.0;
		double roll = 0.0;

		float angles = 0.0f;
	public:
		//initialize with (0,0,0)
		static constexpr glm::vec3 Zero = glm::vec3(0.0f, 0.0f, 0.0f);

	};
}