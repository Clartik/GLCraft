#pragma once

#include <Engine.h>

class MainLayer : public Engine::Layer
{
public:
	MainLayer(const std::string& name);
	~MainLayer();

	void OnAttach();
	void OnDetach();
	void OnUpdate();
	void OnEvent(Engine::Event& e);
};