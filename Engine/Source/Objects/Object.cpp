#include "actapch.h"
#include "Object.h"
#include "catch.hpp"

extern float yaw;
extern float pitch;

void Object::Init()
{
	transform = glm::mat4(1.0f);
}

void Object::SetPosition(const glm::vec3& position)
{
	m_position = position;
	transform = glm::translate(transform, m_position);
}

void Object::SetPosition(const float& x, const float& y, const float& z)
{
	m_position = glm::vec3(x, y, z);
	transform = glm::translate(transform, m_position);
}

glm::vec3 Object::GetPosition()
{
	return m_position;
}

void Object::SetRotation(const float& angle, const glm::vec3& rotation)
{
	m_rotation = rotation;
	transform = glm::rotate(transform, glm::radians(angle), m_rotation);
}

glm::vec3 Object::GetRotation()
{
	return m_rotation;
}

void Object::SetScale(const glm::vec3& scale)
{
	m_scale = scale;
	transform = glm::scale(transform, m_scale);
}

glm::vec3 Object::GetScale()
{
	return m_scale;
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
