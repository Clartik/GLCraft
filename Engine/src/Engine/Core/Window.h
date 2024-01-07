#pragma once

#include "Engine/Events/Event.h"

namespace Engine
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width, Height;

		WindowProps(
			const std::string title = "App",
			unsigned int width = 960,
			unsigned int height = 540)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event& e)>;
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
	};
}