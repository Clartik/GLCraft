#pragma once

#include <Engine.h>

class MainLayer : public Engine::Layer
{
public:
	MainLayer();
	~MainLayer();

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate(Engine::DeltaTime deltaTime) override;
	void OnEvent(Engine::Event& e) override;
private:
	std::shared_ptr<Engine::VertexArray> m_VAO;
	std::shared_ptr<Engine::Shader> m_Shader;

	std::shared_ptr<Engine::Camera> m_Camera;
	glm::mat4 m_Transform;
};