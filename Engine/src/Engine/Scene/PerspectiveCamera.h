#pragma once

#include "Camera.h"

namespace Engine
{
	class PerspectiveCamera : public Camera
	{
	public:
		struct ProjectionDetails
		{
			float FOV;
			float AspectRatio;
			float NearPlane;
			float FarPlane;

			ProjectionDetails(float fov, float aspectRatio, float nearPlane, float farPlane)
				: FOV(fov), AspectRatio(aspectRatio), NearPlane(nearPlane), FarPlane(farPlane)
			{
			}
		};
	public:
		PerspectiveCamera(const ProjectionDetails& projectionDetails,
			const glm::vec3& position, const glm::vec3& lookAt, const glm::vec3& up);

		const glm::vec3& GetPosition() const { return m_Position; }
		const float& GetRotation() const { return m_Rotation; }

		void SetPosition(const glm::vec3& position);
		void SetRotation(float rotation);

		void SetView(const glm::vec3& pos, const glm::vec3& lookAt, const glm::vec3& up);
		void SetProjection(const ProjectionDetails& projectionDetails);

		inline const glm::mat4& GetProjection() const override { return m_Proj; }
		inline const glm::mat4& GetView() const override { return m_View; }
		inline const glm::mat4& GetViewProjection() const override { return m_ViewProj; }
	private:
		void RecalculateView() override;
	private:
		glm::mat4 m_Proj, m_View;
		glm::mat4 m_ViewProj;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;
	};
}