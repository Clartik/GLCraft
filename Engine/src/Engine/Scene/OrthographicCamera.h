#pragma once

#include "Camera.h"

namespace Engine
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right, float top, float bottom, const Transform& transform, 
			float nearPlane = -1.0f, float farPlane = 1.0f);

		void SetClippingPlanes(float left, float right, float top, float bottom, 
			float nearPlane = -1.0f, float farPlane = 1.0f);

		virtual void LookAt(const glm::vec3& lookAt) override;

		inline virtual const glm::mat4& GetProjection() const override { return m_Proj; }
		inline virtual const glm::mat4& GetView() const override { return m_View; }
		inline virtual const glm::mat4& GetViewProjection() const override { return m_ViewProj; }

		inline virtual Transform& GetTransform() override { return m_Transform; }
	private:
		virtual void SetProjection() override;
		inline virtual void CalculateViewProjection() override
		{
			m_View = glm::inverse(m_Transform.GetMatrix());
			m_ViewProj = m_Proj * m_View;
		}
	private:
		struct CameraData
		{
			float LeftPlane;
			float RightPlane;
			float TopPlane;
			float BottomPlane;
			float NearPlane;
			float FarPlane;

			CameraData(float left, float right, float top, float bottom, float nearPlane, float farPlane)
				: LeftPlane(left), RightPlane(right), TopPlane(top), BottomPlane(bottom), NearPlane(nearPlane),
				FarPlane(farPlane)
			{
			}
		};

		CameraData m_Data;

		glm::mat4 m_Proj, m_View;
		glm::mat4 m_ViewProj;

		Transform m_Transform;
	};
}