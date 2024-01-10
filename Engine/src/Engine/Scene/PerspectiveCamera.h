#pragma once

#include "Camera.h"

namespace Engine
{
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(float fov, float aspectRatio, float nearPlane, float farPlane,
			const glm::vec3& position);

		inline const glm::vec3& GetPosition() const override { return m_Position; }
		inline const float& GetRotation() const override { return m_Rotation; }

		void SetPosition(const glm::vec3& position) override;
		void SetRotation(float rotation) override;

		inline const glm::vec3& GetFront() const { return m_Front; }
		inline const glm::vec3& GetRight() const { return m_Right; }
		inline const glm::vec3& GetUp() const { return m_Up; }

		void SetFront(const glm::vec3& frontVec);

		void LookAt(const glm::vec3& lookAt);
		void SetProjection(float fov, float aspectRatio, float nearPlane, float farPlane);

		inline const glm::mat4& GetProjection() const override { return m_Proj; }
		inline const glm::mat4& GetView() const override { return m_View; }
		inline const glm::mat4& GetViewProjection() const override { return m_ViewProj; }
	private:
		void RecalculateView() override;
		inline void RecalculateViewProjection() override { m_ViewProj = m_Proj * m_View; }
	private:
		glm::mat4 m_Proj, m_View;
		glm::mat4 m_ViewProj;

		glm::vec3 m_Position;
		float m_Rotation = 0.0f;

		glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 m_Right = glm::vec3(0.0f);
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	};
}