#include "pch.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"

namespace Engine
{
	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
		return std::make_unique<WindowsWindow>(props);
	}
}