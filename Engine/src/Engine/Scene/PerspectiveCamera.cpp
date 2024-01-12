#include "pch.h"
#include "PerspectiveCamera.h"

namespace Engine
{
	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane, 
		const Transform& transform)
		: m_Data(fov, aspectRatio, nearPlane, farPlane), m_Transform(transform)
	{
		m_Transform.AddMatrixUpdateCallback(std::bind(&PerspectiveCamera::CalculateViewProjection, this));
		SetProjection();
	}

	void PerspectiveCamera::LookAt(const glm::vec3& lookAt)
	{
		m_View = glm::lookAt(m_Transform.GetPosition(), lookAt, m_Transform.GetUp());
		m_Transform.SetMatrix(glm::inverse(m_View));

		CalculateViewProjection();
	}

	void PerspectiveCamera::SetFOV(float fov)
	{
		m_Data.FOV = fov;
		SetProjection();
	}

	void PerspectiveCamera::SetAspectRatio(float aspectRatio)
	{
		m_Data.AspectRatio = aspectRatio;
		SetProjection();
	}

	void PerspectiveCamera::SetProjection()
	{
		m_Proj = glm::perspective(m_Data.FOV, m_Data.AspectRatio, m_Data.NearPlane, m_Data.FarPlane);
		CalculateViewProjection();
	}
}