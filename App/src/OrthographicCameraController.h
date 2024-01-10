#pragma once

#include <Engine.h>

class OrthographicCameraController
{
public:
	OrthographicCameraController(float aspectRatio, const glm::vec3& position, float zoomLevel = 1.0f);
	~OrthographicCameraController();

	void OnUpdate(Engine::DeltaTime deltaTime);
	void OnEvent(Engine::Event& e);

	inline Engine::OrthographicCamera& GetCamera() { return m_Camera; }
	inline const Engine::OrthographicCamera& GetCamera() const { return m_Camera; }
	
	bool OnMouseScrolled(Engine::MouseScrolledEvent& e);
private:
	float m_AspectRatio;
	float m_ZoomLevel;

	Engine::OrthographicCamera m_Camera;

	float m_MoveSpeed = 5.0f;
	float m_RotationSpeed = 5.0f;
	float m_ZoomAmount = 0.25f;
};