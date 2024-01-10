#include "pch.h"
#include "Engine/Core/Time.h"

#include <GLFW/glfw3.h>

namespace Engine
{
	float Time::GetTime()
	{
		return glfwGetTime();
	}
}