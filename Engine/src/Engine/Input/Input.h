#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

#include <glm/glm.hpp>

namespace Engine
{
	class Input
	{
	public:
		enum class MouseState
		{
			NORMAL = 0,
			LOCKED = 1
		};
	public:
		static void Init();

		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMousePosX();
		static float GetMousePosY();
		static glm::vec2 GetMouseOffset();
		static float GetMouseOffsetX();
		static float GetMouseOffsetY();
		static MouseState GetMouseState();
		static void SetMouseState(MouseState mouseState);
		static void SetMouseVisiblity(bool enabled);
	private:
		static glm::vec2 m_LastMousePos;
	};
}