#pragma once

#include "Core.h"
#include "Engine/Events/Event.h"

namespace Engine
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer")
			: m_DebugName(name) { }
		virtual ~Layer() {}

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& e) {}

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}