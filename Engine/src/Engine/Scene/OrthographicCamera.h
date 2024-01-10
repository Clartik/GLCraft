#pragma once

#include "Camera.h"

namespace Engine
{
	class OrthographicCamera : public Camera
	{
	public:
		struct ProjectionDetails
		{
			float AspectRatio;
			float LeftPlane;
			float RightPlane;
			float TopPlane;
			float BottomPlane;
			float NearPlane;
			float FarPlane;

			ProjectionDetails(float aspectRatio,
				float left, float right, 
				float top, float bottom, 
				float nearPlane = -1.0f, float farPlane = 1.0f)
				: AspectRatio(aspectRatio),
				LeftPlane(left), RightPlane(right), 
				TopPlane(top), BottomPlane(bottom),
				NearPlane(nearPlane), FarPlane(farPlane)
			{
				// Adjust the projection matrix based on the aspect ratio
				if (AspectRatio > 1.0f)
				{
					// If the screen is wider than tall, adjust the vertical extents
					BottomPlane /= AspectRatio;
					TopPlane /= AspectRatio;
				}
				else
				{
					// If the screen is taller than wide, adjust the horizontal extents
					LeftPlane *= AspectRatio;
					RightPlane *= AspectRatio;
				}
			}
		};
	public:
		OrthographicCamera(const ProjectionDetails& projectionDetails, const glm::vec3& pos);
		
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