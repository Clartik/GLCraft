#include "pch.h"
#include "PerspectiveCamera.h"

namespace Engine
{
	PerspectiveCamera::PerspectiveCamera(const ProjectionDetails& projectionDetails,
		const glm::vec3& pos, const glm::vec3& lookAt, const glm::vec3& up)
	{
		SetProjection(projectionDetails);
		SetView(pos, lookAt, up);
		RecalculateView();
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

	void PerspectiveCamera::SetView(const glm::vec3& pos, const glm::vec3& lookAt, const glm::vec3& up)
	{
		m_View = glm::lookAt(pos, lookAt, up);
	}

	void PerspectiveCamera::SetProjection(const PerspectiveCamera::ProjectionDetails& projectionDetails)
	{
		m_Proj = glm::perspective(projectionDetails.FOV, projectionDetails.AspectRatio,
			projectionDetails.NearPlane, projectionDetails.FarPlane);
	}

	void PerspectiveCamera::RecalculateView()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		// Camera Movement Should Make the Model Matrix of Objects Go Opposite Way
		m_View = glm::inverse(transform);
		m_ViewProj = m_Proj * m_View;
	}
}