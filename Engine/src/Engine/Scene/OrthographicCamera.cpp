#include "pch.h"
#include "OrthographicCamera.h"

namespace Engine
{
	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, 
		const glm::vec3& position, float nearPlane, float farPlane)
		: m_Position(position)
	{
		m_Proj = glm::ortho(left, right, top, bottom, nearPlane, farPlane);
		CalculateViewProjection();
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateView();
	}

	void OrthographicCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RecalculateView();
	}

	void OrthographicCamera::LookAt(const glm::vec3& lookAt)
	{
		m_View = glm::lookAt(m_Position, lookAt, m_Up);
		CalculateViewProjection();
	}

	void OrthographicCamera::SetProjection(float left, float right, float top, float bottom,
		float nearPlane, float farPlane)
	{
		m_Proj = glm::ortho(left, right, top, bottom, nearPlane, farPlane);
		CalculateViewProjection();
	}

	void OrthographicCamera::RecalculateView()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		// Camera Movement Should Make the Model Matrix of Objects Go Opposite Way
		m_View = glm::inverse(transform);
		CalculateViewProjection();
	}
}