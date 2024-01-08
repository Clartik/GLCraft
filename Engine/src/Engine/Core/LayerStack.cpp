#include "pch.h"
#include "LayerStack.h"

namespace Engine
{
	Engine::LayerStack::LayerStack()
	{
	}

	Engine::LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void Engine::LayerStack::PushLayer(Layer* layer)
	{
		layer->OnAttach();
		m_Layers.emplace_back(layer);
	}

	void Engine::LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it == m_Layers.end())
		{
			CORE_LOG_ERROR("Could Not Pop Layer: {0}", layer->GetName());
			return;
		}

		layer->OnDetach();
		m_Layers.erase(it);
	}
}
