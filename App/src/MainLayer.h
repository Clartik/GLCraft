#pragma once

#include <Engine.h>

class MainLayer : public Engine::Layer
{
public:
	MainLayer();
	~MainLayer();

	void OnAttach();
	void OnDetach();
	void OnUpdate();
	void OnEvent(Engine::Event& e);
private:
	Engine::VertexArray* m_VAO;

	std::shared_ptr<Engine::Shader> m_Shader;
};