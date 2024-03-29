#include "pch.h"
#include "Application.h"

#include "Engine/Input/Input.h"

#include "Time.h"
#include "DeltaTime.h"

namespace Engine
{
	Application* Application::s_Instance = nullptr;

	Application::Application(const std::string& title)
	{
		Log::Init();

		CORE_ASSERT(!s_Instance, "Application is Already Initalized!");
		s_Instance = this;

		m_Window = Window::Create(WindowProps(title));
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Input::Init();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			float currentTime = Time::GetTime();
			DeltaTime deltaTime = currentTime - m_LastFrameTime;
			m_LastFrameTime = currentTime;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(deltaTime);

			m_Window->OnUpdate();
		}
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
