#pragma once

#include "Camera.h"
#include "Engine/Core/DeltaTime.h"

namespace Engine
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane,
			const Transform& transform);

		void SetFOV(float fov);
		void SetAspectRatio(float aspectRatio);

		void LookAt(const glm::vec3& lookAt);

		inline const glm::mat4& GetProjection() const override { return m_Proj; }
		inline const glm::mat4& GetView() const override { return m_View; }
		inline const glm::mat4& GetViewProjection() const override { return m_ViewProj; }

		inline Transform& GetTransform() override { return m_Transform; }
	private:
		void SetProjection();

		inline void CalculateViewProjection() override 
		{ 
			m_View = glm::inverse(m_Transform.GetMatrix());
			m_ViewProj = m_Proj * m_View;
		}
	private:
		struct CameraData
		{
			float FOV;
			float AspectRatio;
			float NearPlane;
			float FarPlane;

			CameraData(float fov, float aspectRatio, float nearPlane, float farPlane)
				: FOV(fov), AspectRatio(aspectRatio), NearPlane(nearPlane), FarPlane(farPlane) 
			{}
		};

		CameraData m_Data;

		glm::mat4 m_Proj, m_View;
		glm::mat4 m_ViewProj;

		Transform m_Transform;
	};
}