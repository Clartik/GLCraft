#pragma once

#include "Engine/Core/Window.h"
#include "Engine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Engine
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		inline bool IsVSync() const override { return m_Data.VSync; }

		inline void* GetNativeWindow() const { return m_Window; }
	private:
		void Init(const WindowProps& props);
		void Shutdown();
	private:
		GLFWwindow* m_Window = nullptr;
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width = 0, Height = 0;
			bool VSync = false;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}