#include "pch.h"
#include "PerspectiveCameraController.h"

PerspectiveCameraController::PerspectiveCameraController(float fov, float aspectRatio, 
	float nearPlane, float farPlane, const glm::vec3& position)
	: m_Camera(fov, aspectRatio, nearPlane, farPlane, position)
{
	const Engine::Window& window = Engine::Application::Get().GetWindow();

	m_LastX = window.GetWidth();
	m_LastY = window.GetHeight();
}

void PerspectiveCameraController::OnUpdate(Engine::DeltaTime deltaTime)
{
	glm::vec3 pos = m_Camera.GetPosition();

	if (Engine::Input::IsKeyPressed(Engine::Key::W))
	{
		pos += m_MoveSpeed * deltaTime * m_Camera.GetFront();
	}

	if (Engine::Input::IsKeyPressed(Engine::Key::S))
	{
		pos -= m_MoveSpeed * deltaTime * m_Camera.GetFront();
	}

	if (Engine::Input::IsKeyPressed(Engine::Key::A))
	{
		pos -= m_MoveSpeed * deltaTime * m_Camera.GetRight();
	}

	if (Engine::Input::IsKeyPressed(Engine::Key::D))
	{
		pos += m_MoveSpeed * deltaTime * m_Camera.GetRight();
	}

	//Engine::LOG_INFO("Position: {0}, {1}, {2}", pos.x, pos.y, pos.z);

	m_Camera.SetPosition(pos);
}

void PerspectiveCameraController::OnEvent(Engine::Event& e)
{
	Engine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Engine::MouseMovedEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
	dispatcher.Dispatch<Engine::MouseScrolledEvent>(BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
}

bool PerspectiveCameraController::OnMouseMoved(Engine::MouseMovedEvent& e)
{
	if (!Engine::Input::IsMouseButtonPressed(Engine::Mouse::ButtonRight))
	{
		Engine::Input::UnlockMousePos();
		return false;
	}

	Engine::Input::LockMousePos();

	float xOffset = e.GetX() - m_LastX;
	float yOffset = m_LastY - e.GetY();

	m_LastX = xOffset;
	m_LastY = yOffset;

	m_Yaw += xOffset * m_RotationSpeed;
	m_Pitch += yOffset * m_RotationSpeed;

	glm::vec3 direction;
	direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	direction.y = sin(glm::radians(m_Pitch));
	
	direction = glm::normalize(direction);
	m_Camera.SetFront(direction);

	return false;
}

bool PerspectiveCameraController::OnMouseScrolled(Engine::MouseScrolledEvent& e)
{
	return false;
}
