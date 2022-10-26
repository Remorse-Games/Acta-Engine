#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ActaEngine
{
	class Transform
	{
	public:
		/*! Set transform matrix to Identity. */
		void Identity();

		/*! Set transform position. */
		void SetPosition(const glm::vec3& pos);
		/*! Set transform position. */
		void SetPosition(const float& x, const float& y, const float& z);
		
		/*! Set transform rotation using angle. 
		* @param angle angle of the rotated axis.
		* @param rot total rotation want to do. 1 for full rotation 0 for no rotation.
		*/
		void SetRotation(const float& angle, const glm::vec3& rot);
		/*! Set transform rotation using euler angles YXZ. */
		void SetRotationEuler(const glm::vec3& rot);
		/*! Set transform rotation using euler angles YXZ.	*/
		void SetRotationEuler(const float& x, const float& y, const float& z);

		/*! Set transform scale. */
		void SetScale(const glm::vec3& sca);
		/*! Set transform scale. */
		void SetScale(const float& x, const float& y, const float& z);
		
		/*! Get transform position. */
		glm::vec3 GetPosition() const;
		/*! Get transform rottation. */
		glm::vec3 GetRotation() const;
		/*! Get transform scale. */
		glm::vec3 GetScale() const;
		/*! Get transform matrix. used to modify matrix position. */
		glm::mat4 GetTransformMatrix();

	public:
		/*! Forward direction object facing to. */
		glm::vec3 forward;
		/*! Up direction object facing to. */
		glm::vec3 up;
		/*! Right direction object facing to. */
		glm::vec3 right;

		/*! Yaw tilt object horizontally for rotation. */
		double yaw = 0.0;
		/*! Pitch tilt object vertically for rotation. */
		double pitch = 0.0;
		/*! roll tilt object rolling for rotation. */
		double roll = 0.0;

		/*! Direction where object facing to. */
		glm::vec3 direction;

	private:
		/*! member variable to store matrix location. */
		glm::mat4 m_Transform = glm::mat4(0.0f);

		/*! member variable storing position. */
		glm::vec3 m_Position = glm::vec3(0.0f);
		/*! member variable to store rotation. */
		glm::vec3 m_Rotation = glm::vec3(0.0f);
		/*! member variable to store scale. */
		glm::vec3 m_Scale = glm::vec3(1.0f);

	public:
		/*! Vector3 equals 0. */
		static constexpr glm::vec3 Zero = glm::vec3(0.0f, 0.0f, 0.0f);

	};
}