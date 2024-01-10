#include "pch.h"
#include "Engine/Input/Input.h"

#include <GLFW/glfw3.h>

#include "Engine/Core/Application.h"

namespace Engine
{
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

	void Input::LockMousePos()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Input::UnlockMousePos()
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	void Input::SetMouseVisiblity(bool enabled)
	{
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwSetInputMode(window, GLFW_CURSOR, enabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
	}
}