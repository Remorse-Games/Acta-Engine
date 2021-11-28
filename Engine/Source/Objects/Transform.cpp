#include "actapch.h"
#include "Transform.h"
#include "catch.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/euler_angles.hpp"

void ActaEngine::Transform::Identity()
{
	m_Transform = glm::mat4(1.0f);
}

void ActaEngine::Transform::SetPosition(const glm::vec3& position)
{
	m_position = position;
	m_Transform = glm::translate(m_Transform, m_position);
}

void ActaEngine::Transform::SetPosition(const float& x, const float& y, const float& z)
{
	m_position = glm::vec3(x, y, z);
	m_Transform = glm::translate(m_Transform, m_position);
}

glm::vec3 ActaEngine::Transform::GetPosition() const
{
	return m_position;
}

void ActaEngine::Transform::SetRotation(const float& angle, const glm::vec3& rotation)
{
	m_rotation = rotation;
	m_Transform = glm::rotate(m_Transform, glm::radians(angle), m_rotation);
}

void ActaEngine::Transform::SetRotationEuler(const glm::vec3& rot)
{
	m_rotation = glm::vec3(rot[0], rot[1], rot[2]);
	m_Transform *= glm::eulerAngleYXZ(rot[0], rot[1], rot[2]);
}

void ActaEngine::Transform::SetRotationEuler(const float& x, const float& y, const float& z)
{
	m_rotation = glm::vec3(x, y, z);
	m_Transform *= glm::eulerAngleYXZ(m_rotation.y, m_rotation.x, m_rotation.z);
}

glm::vec3 ActaEngine::Transform::GetRotation() const
{
	return m_rotation;
}

void ActaEngine::Transform::SetScale(const glm::vec3& scale)
{
	m_scale = scale;
	m_Transform = glm::scale(m_Transform, m_scale);
}

void ActaEngine::Transform::SetScale(const float& x, const float& y, const float& z)
{
	m_scale = glm::vec3(x, y, z);
	m_Transform = glm::scale(m_Transform, m_scale);
}


glm::vec3 ActaEngine::Transform::GetScale() const
{
	return m_scale;
}


#if UNIT_TESTING
TEST_CASE("ObjectFunctions")
{
	auto obj = new Transform;
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
