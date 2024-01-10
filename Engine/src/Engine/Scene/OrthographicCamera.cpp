#include "pch.h"
#include "OrthographicCamera.h"

namespace Engine
{
	OrthographicCamera::OrthographicCamera(const ProjectionDetails& projectionDetails, const glm::vec3& position)
	{
		SetPosition(position);
		SetProjection(projectionDetails);
		m_ViewProj = m_Proj * m_View;
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

	void OrthographicCamera::SetView(const glm::vec3& pos, const glm::vec3& lookAt, const glm::vec3& up)
	{
		m_View = glm::lookAt(pos, lookAt, up);
	}

	void OrthographicCamera::SetProjection(const ProjectionDetails& projectionDetails)
	{
		m_Proj = glm::ortho(
			projectionDetails.LeftPlane, projectionDetails.RightPlane,
			projectionDetails.TopPlane, projectionDetails.BottomPlane,
			projectionDetails.NearPlane, projectionDetails.FarPlane);
	}

	void OrthographicCamera::RecalculateView()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * 
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));

		// Camera Movement Should Make the Model Matrix of Objects Go Opposite Way
		m_View = glm::inverse(transform);
		m_ViewProj = m_Proj * m_View;
	}
}