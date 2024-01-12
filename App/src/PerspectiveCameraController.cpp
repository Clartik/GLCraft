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

	if (Engine::Input::IsKeyPressed(Engine::Key::W))
	{
		pos += m_MoveSpeed * deltaTime * m_Camera.GetTransform().GetForward();
	}

	if (Engine::Input::IsKeyPressed(Engine::Key::S))
	{
		pos -= m_MoveSpeed * deltaTime * m_Camera.GetTransform().GetForward();
	}

	if (Engine::Input::IsKeyPressed(Engine::Key::A))
	{
		pos -= m_MoveSpeed * deltaTime * m_Camera.GetTransform().GetRight();
	}

	if (Engine::Input::IsKeyPressed(Engine::Key::D))
	{
		pos += m_MoveSpeed * deltaTime * m_Camera.GetTransform().GetRight();
	}

	if (Engine::Input::IsMouseButtonPressed(Engine::Mouse::ButtonRight))
	{
		Engine::Input::SetMouseState(Engine::Input::MouseState::LOCKED);
		glm::vec2 offset = Engine::Input::GetMouseOffset();

		m_Yaw += offset.x * m_RotationSpeed;
		m_Pitch += offset.y * m_RotationSpeed;

		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));

		direction = glm::normalize(direction);
	}
	else
	{
		Engine::Input::SetMouseState(Engine::Input::MouseState::NORMAL);
	}

	m_RotationSpeed = 2.0f * deltaTime;

	LOG_INFO("Position: {0}, {1}, {2}", pos.x, pos.y, pos.z);
	m_Camera.GetTransform().SetPosition(pos);
}

void PerspectiveCameraController::OnEvent(Engine::Event& e)
{
	Engine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Engine::MouseMovedEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
	dispatcher.Dispatch<Engine::MouseScrolledEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
}

bool PerspectiveCameraController::OnMouseMoved(Engine::MouseMovedEvent& e)
{
	return false;
}

bool PerspectiveCameraController::OnMouseScrolled(Engine::MouseScrolledEvent& e)
{
	return false;
}
