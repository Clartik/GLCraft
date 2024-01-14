#include "pch.h"
#include "OrthographicCamera.h"

namespace Engine
{
	OrthographicCamera::OrthographicCamera(float left, float right, float top, float bottom, 
		const Transform& transform, float nearPlane, float farPlane)
		: m_Data(left, right, top, bottom, nearPlane, farPlane), m_Transform(transform)
	{
		m_Transform.AddMatrixUpdateCallback(std::bind(&OrthographicCamera::CalculateViewProjection, this));
		SetProjection();
	}

	void OrthographicCamera::SetClippingPlanes(float left, float right, float top, float bottom, 
		float nearPlane, float farPlane)
	{
		m_Data = CameraData(left, right, top, bottom, nearPlane, farPlane);
		SetProjection();
	}

	void OrthographicCamera::LookAt(const glm::vec3& lookAt)
	{
		m_View = glm::lookAt(m_Transform.GetPosition(), lookAt, m_Transform.GetUp());
		m_Transform.SetMatrix(glm::inverse(m_View));

		CalculateViewProjection();
	}

	void OrthographicCamera::SetProjection()
	{
		m_Proj = glm::ortho(m_Data.LeftPlane, m_Data.RightPlane, m_Data.TopPlane, m_Data.BottomPlane, 
			m_Data.NearPlane, m_Data.FarPlane);
		CalculateViewProjection();
	}
}