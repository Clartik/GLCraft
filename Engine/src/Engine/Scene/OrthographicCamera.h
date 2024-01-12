#pragma once

#include "Camera.h"

namespace Engine
{
	class OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera(float left, float right,
			float top, float bottom,
			const glm::vec3& position,
			float nearPlane = -1.0f, float farPlane = 1.0f);
		
		const glm::vec3& GetPosition() const { return m_Position; }
		const float& GetEulerRotation() const { return m_Rotation; }

		void SetPosition(const glm::vec3& position);
		void SetRotation(float rotation);

		void LookAt(const glm::vec3& lookAt) override;

		void SetProjection(float left, float right,
			float top, float bottom,
			float nearPlane = -1.0f, float farPlane = 1.0f);

		inline const glm::mat4& GetProjection() const override { return m_Proj; }
		inline const glm::mat4& GetView() const override { return m_View; }
		inline const glm::mat4& GetViewProjection() const override { return m_ViewProj; }
	private:
		inline void CalculateViewProjection() override { m_ViewProj = m_Proj * m_View; }
	private:
		glm::mat4 m_Proj, m_View;
		glm::mat4 m_ViewProj;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;

		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	};
}