#include "actapch.h"
#include "Transform.h"
#include "catch.hpp"

float yaw = 0.0f;
float pitch = 0.0f;
float roll = 0.0f;

void Transform::Identity()
{
	transform = glm::mat4(1.0f);
}

void Transform::SetPosition(const glm::vec3& position)
{
	m_position = position;
	transform = glm::translate(transform, m_position);
}

void Transform::SetPosition(const float& x, const float& y, const float& z)
{
	m_position = glm::vec3(x, y, z);
	transform = glm::translate(transform, m_position);
}

glm::vec3 Transform::GetPosition() const
{
	return m_position;
}

void Transform::SetRotation(const float& angle, const glm::vec3& rotation)
{
	m_rotation = rotation;
	transform = glm::rotate(transform, glm::radians(angle), m_rotation);
}

glm::vec3 Transform::GetRotation() const
{
	return m_rotation;
}

void Transform::SetScale(const glm::vec3& scale)
{
	m_scale = scale;
	transform = glm::scale(transform, m_scale);
}

glm::vec3 Transform::GetScale() const
{
	return m_scale;
}

void Transform::UpdateDirection()
{
	glm::vec3 direction;
	glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
	Forward = glm::normalize(direction);
	Right = glm::normalize(glm::cross(worldUp, Forward));
	Up = glm::cross(Forward, Right);
}

#if UNIT_TESTING
TEST_CASE("ObjectFunctions")
{
	auto obj = new Object;
	SECTION("GetPosition And SetPosition (By Floats)")
	{
		obj->SetPosition(1, 2, 3);

		REQUIRE(obj->GetPosition().x == 1);
		REQUIRE(obj->GetPosition().y == 2);
		REQUIRE(obj->GetPosition().z == 3);
		REQUIRE(obj->GetPosition() == glm::vec3(1, 2, 3));
	}
	SECTION("GetPosition And SetPosition (By Vector3)")
	{
		obj->SetPosition(glm::vec3(4, 5, 6));

		REQUIRE(obj->GetPosition().x == 4);
		REQUIRE(obj->GetPosition().y == 5);
		REQUIRE(obj->GetPosition().z == 6);
		REQUIRE(obj->GetPosition() == glm::vec3(4, 5, 6));
	}
	SECTION("GetRotation And SetRotation")
	{
		obj->SetRotation(55, glm::vec3(7, 8, 9));

		REQUIRE(obj->GetRotation().x == 7);
		REQUIRE(obj->GetRotation().y == 8);
		REQUIRE(obj->GetRotation().z == 9);
		REQUIRE(obj->GetRotation() == glm::vec3(7, 8, 9));
	}
	SECTION("GetScale And SetScale")
	{
		obj->SetScale(glm::vec3(10, 11, 12));

		REQUIRE(obj->GetScale().x == 10);
		REQUIRE(obj->GetScale().y == 11);
		REQUIRE(obj->GetScale().z == 12);
		REQUIRE(obj->GetScale() == glm::vec3(10, 11, 12));
	}
}
#endif
