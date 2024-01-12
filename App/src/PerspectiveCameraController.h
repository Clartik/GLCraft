#pragma once

#include <Engine.h>

class PerspectiveCameraController
{
public:
	PerspectiveCameraController(float fov, float aspectRatio, float nearPlane, float farPlane, 
		const Engine::Transform& transform);

	void OnUpdate(Engine::DeltaTime deltaTime);
	void OnEvent(Engine::Event& e);

	bool OnMouseMoved(Engine::MouseMovedEvent& e);
	bool OnMouseScrolled(Engine::MouseScrolledEvent& e);

	inline Engine::PerspectiveCamera& GetCamera() { return m_Camera; }
	inline const Engine::PerspectiveCamera& GetCamera() const { return m_Camera; }
private:
	Engine::PerspectiveCamera m_Camera;

	float m_MoveSpeed = 5.0f;
	float m_RotationSpeed = 25.0f;
	float m_Yaw = 0.0f, m_Pitch = 0.0f;
};