#include "pch.h"
#include "PerspectiveCameraController.h"

PerspectiveCameraController::PerspectiveCameraController(float fov, float aspectRatio, 
	float nearPlane, float farPlane, const Engine::Transform& transform)
	: m_Camera(fov, aspectRatio, nearPlane, farPlane, transform)
{
}

void PerspectiveCameraController::OnUpdate(Engine::DeltaTime deltaTime)
{
	glm::vec3 pos = m_Camera.GetTransform().GetPosition();

	//LOG_INFO("Position: {0}, {1}, {2}", pos.x, pos.y, pos.z);

	if (Engine::Input::IsKeyPressed(Engine::Key::W))
		pos -= m_MoveSpeed * deltaTime * m_Camera.GetTransform().GetForward();

	if (Engine::Input::IsKeyPressed(Engine::Key::S))
		pos += m_MoveSpeed * deltaTime * m_Camera.GetTransform().GetForward();

	if (Engine::Input::IsKeyPressed(Engine::Key::A))
		pos -= m_MoveSpeed * deltaTime * m_Camera.GetTransform().GetRight();

	if (Engine::Input::IsKeyPressed(Engine::Key::D))
		pos += m_MoveSpeed * deltaTime * m_Camera.GetTransform().GetRight();

	if (Engine::Input::IsKeyPressed(Engine::Key::Q))
		pos -= m_MoveSpeed * deltaTime * m_Camera.GetTransform().GetUp();

	if (Engine::Input::IsKeyPressed(Engine::Key::E))
		pos += m_MoveSpeed * deltaTime * m_Camera.GetTransform().GetUp();

	if (Engine::Input::IsMouseButtonPressed(Engine::Mouse::ButtonRight))
	{
		Engine::Input::SetMouseState(Engine::Input::MouseState::LOCKED);
		glm::vec2 offset = Engine::Input::GetMouseOffset();

		m_Yaw = offset.x * m_RotationSpeed * deltaTime;
		m_Pitch = -offset.y * m_RotationSpeed * deltaTime;

		Engine::Transform& camTransform = m_Camera.GetTransform();

		camTransform.Rotate({ m_Pitch, m_Yaw, 0.0f });
	}
	else
		Engine::Input::SetMouseState(Engine::Input::MouseState::NORMAL);

	m_Camera.GetTransform().SetPosition(pos);
}