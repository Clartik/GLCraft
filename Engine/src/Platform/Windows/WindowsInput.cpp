#include "pch.h"
#include "Engine/Input/Input.h"

#include <GLFW/glfw3.h>

#include "Engine/Core/Application.h"

namespace Engine
{
	glm::vec2 Input::m_LastMousePos;
	bool Input::m_FirstMouseMove = true;

	bool Input::IsKeyPressed(KeyCode key)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, key);
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}
	
	glm::vec2 Input::GetMousePosition()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos = 0, yPos = 0;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	float Input::GetMousePosX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMousePosY()
	{
		return GetMousePosition().y;
	}

	glm::vec2 Input::GetMouseOffset()
	{
		glm::vec2 mousePos = GetMousePosition();

		if (m_FirstMouseMove)
		{
			m_LastMousePos = mousePos;
			m_FirstMouseMove = false;
		}

		glm::vec2 offset;
		offset.x = mousePos.x - m_LastMousePos.x;
		offset.y = m_LastMousePos.y - mousePos.y;

		m_LastMousePos = mousePos;

		return offset;
	}

	float Input::GetMouseOffsetX()
	{
		return GetMouseOffset().x;
	}

	float Input::GetMouseOffsetY()
	{
		return GetMouseOffset().y;
	}

	Input::MouseState Input::GetMouseState()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetInputMode(window, GLFW_CURSOR);

		switch (state)
		{
		case GLFW_CURSOR_NORMAL:
			return MouseState::NORMAL;
		case GLFW_CURSOR_DISABLED:
			return MouseState::LOCKED;
		default:
			break;
		}

		return MouseState::NORMAL;
	}

	void Input::SetMouseState(MouseState mouseState)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		switch (mouseState)
		{
		case Engine::Input::MouseState::NORMAL:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;
		case Engine::Input::MouseState::LOCKED:
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		default:
			break;
		}
	}

	void Input::SetMouseVisiblity(bool enabled)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwSetInputMode(window, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
	}
}