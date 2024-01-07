#pragma once

#include "Window.h"

#include "Engine/Events/ApplicationEvent.h"

namespace Engine
{
	class Application
	{
	public:
		Application(const std::string& title);
		~Application();

		void Run();
	private:
		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		bool m_Running = true;

		std::unique_ptr<Window> m_Window = nullptr;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}