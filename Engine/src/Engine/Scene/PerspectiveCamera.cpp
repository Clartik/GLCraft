#include "pch.h"
#include "PerspectiveCamera.h"

namespace Engine
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane,
		const glm::vec3& position)
		: m_Position(position)
	{
		m_Proj = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
		RecalculateViewProjection();

		m_Right = glm::normalize(glm::cross(m_Front, m_Up));
	}

	void PerspectiveCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateView();
	}

	void PerspectiveCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RecalculateView();
	}

	void PerspectiveCamera::SetFront(const glm::vec3& frontVec)
	{
		m_Front = frontVec;
		LookAt(m_Position + m_Front);
	}

	void PerspectiveCamera::LookAt(const glm::vec3& lookAt)
	{
		m_View = glm::lookAt(m_Position, lookAt, m_Up);
		RecalculateViewProjection();
	}

	void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		m_Proj = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
		RecalculateViewProjection();
	}

	void PerspectiveCamera::RecalculateView()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		// Camera Movement Should Make the Model Matrix of Objects Go Opposite Way
		m_View = glm::inverse(transform);
		RecalculateViewProjection();
	}
}