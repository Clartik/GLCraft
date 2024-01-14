#include "pch.h"
#include "OrthographicCameraController.h"

OrthographicCameraController::OrthographicCameraController(float aspectRatio, 
	const Engine::Transform& transform, float zoomLevel)
	: m_AspectRatio(aspectRatio), m_ZoomLevel(zoomLevel), 
	m_Camera(-aspectRatio * m_ZoomLevel, aspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, 
		Engine::Transform(transform))
{
}

OrthographicCameraController::~OrthographicCameraController()
{
}

void OrthographicCameraController::OnUpdate(Engine::DeltaTime deltaTime)
{
	Engine::Transform& camTransform = m_Camera.GetTransform();
	glm::vec3 pos = camTransform.GetPosition();
	glm::vec3 rotation = camTransform.GetEulerRotation();

	if (Engine::Input::IsKeyPressed(Engine::Key::W))
		pos += m_MoveSpeed * deltaTime * camTransform.GetUp();

	if (Engine::Input::IsKeyPressed(Engine::Key::S))
		pos -= m_MoveSpeed * deltaTime * camTransform.GetUp();

	if (Engine::Input::IsKeyPressed(Engine::Key::A))
		pos -= m_MoveSpeed * deltaTime * camTransform.GetRight();

	if (Engine::Input::IsKeyPressed(Engine::Key::D))
		pos += m_MoveSpeed * deltaTime * camTransform.GetRight();

	if (Engine::Input::IsKeyPressed(Engine::Key::Q))
		rotation -= m_RotationSpeed * deltaTime * glm::vec3(0, 0, 1);

	if (Engine::Input::IsKeyPressed(Engine::Key::E))
		rotation += m_RotationSpeed * deltaTime * glm::vec3(0, 0, 1);

	camTransform.SetPosition(pos);
	camTransform.SetRotation(rotation);
}

void OrthographicCameraController::OnEvent(Engine::Event& e)
{
	Engine::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Engine::MouseScrolledEvent>(BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
}

bool OrthographicCameraController::OnMouseScrolled(Engine::MouseScrolledEvent& e)
{
	float yScroll = e.GetMouseYOffset();
	m_ZoomLevel -= m_ZoomAmount * yScroll;

	float horizontal = m_AspectRatio * m_ZoomLevel;
	m_Camera.SetClippingPlanes(-horizontal, horizontal, -m_ZoomLevel, m_ZoomLevel);

	return true;
}
