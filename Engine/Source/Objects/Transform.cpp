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
	m_Position = position;
	m_Transform = glm::translate(m_Transform, m_Position);
}

void ActaEngine::Transform::SetPosition(const float& x, const float& y, const float& z)
{
	m_Position = glm::vec3(x, y, z);
	m_Transform = glm::translate(m_Transform, m_Position);
}

glm::vec3 ActaEngine::Transform::GetPosition() const
{
	return m_Position;
}

void ActaEngine::Transform::SetRotation(const float& angle, const glm::vec3& rotation)
{
	m_Rotation = rotation;
	m_Transform = glm::rotate(m_Transform, glm::radians(angle), m_Rotation);
}

void ActaEngine::Transform::SetRotationEuler(const glm::vec3& rot)
{
	m_Rotation = glm::vec3(rot[0], rot[1], rot[2]);
	m_Transform *= glm::eulerAngleYXZ(rot[0], rot[1], rot[2]);
}

void ActaEngine::Transform::SetRotationEuler(const float& x, const float& y, const float& z)
{
	m_Rotation = glm::vec3(x, y, z);
	m_Transform *= glm::eulerAngleYXZ(m_Rotation.y, m_Rotation.x, m_Rotation.z);
}

glm::vec3 ActaEngine::Transform::GetRotation() const
{
	return m_Rotation;
}

void ActaEngine::Transform::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
	m_Transform = glm::scale(m_Transform, m_Scale);
}

void ActaEngine::Transform::SetScale(const float& x, const float& y, const float& z)
{
	m_Scale = glm::vec3(x, y, z);
	m_Transform = glm::scale(m_Transform, m_Scale);
}

glm::vec3 ActaEngine::Transform::GetScale() const
{
	return m_Scale;
}

glm::mat4 ActaEngine::Transform::GetTransformMatrix()
{
	return m_Transform;
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
