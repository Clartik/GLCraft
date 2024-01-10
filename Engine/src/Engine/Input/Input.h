#pragma once

#include "KeyCodes.h"
#include "MouseCodes.h"

#include <glm/glm.hpp>

namespace Engine
{
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMousePosX();
		static float GetMousePosY();
		static void LockMousePos();
		static void UnlockMousePos();
		static void SetMouseVisiblity(bool enabled);
	};
}