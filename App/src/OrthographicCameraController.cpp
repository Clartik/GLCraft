#include "pch.h"
#include "OrthographicCameraController.h"

OrthographicCameraController::OrthographicCameraController(float aspectRatio, const glm::vec3& position, float zoomLevel)
	: m_AspectRatio(aspectRatio), m_ZoomLevel(zoomLevel), 
	m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, position)
{
}

OrthographicCameraController::~OrthographicCameraController()
{
}

void OrthographicCameraController::OnUpdate(Engine::DeltaTime deltaTime)
{
	glm::vec3 pos = m_Camera.GetPosition();

	if (Engine::Input::IsKeyPressed(Engine::Key::W))
	{
		pos.y += m_MoveSpeed * deltaTime;
	}

	if (Engine::Input::IsKeyPressed(Engine::Key::S))
	{
		pos.y -= m_MoveSpeed * deltaTime;
	}

	if (Engine::Input::IsKeyPressed(Engine::Key::A))
	{
		pos.x -= m_MoveSpeed * deltaTime;
	}

	if (Engine::Input::IsKeyPressed(Engine::Key::D))
	{
		pos.x += m_MoveSpeed * deltaTime;
	}

	m_Camera.SetPosition(pos);
}

void OrthographicCameraController::OnEvent(Engine::Event& e)
{
	Engine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Engine::MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
}

bool OrthographicCameraController::OnMouseScrolled(Engine::MouseScrolledEvent& e)
{
	float yScroll = e.GetYOffset();
	m_ZoomLevel -= m_ZoomAmount * yScroll;

	float horizontal = m_AspectRatio * m_ZoomLevel;
	m_Camera.SetProjection(-horizontal, horizontal, -m_ZoomLevel, m_ZoomLevel);

	return true;
}
