#pragma once

#include <Engine.h>

#include "OrthographicCameraController.h"
#include "PerspectiveCameraController.h"

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
	std::shared_ptr<Engine::Shader> m_Shader;

	//std::unique_ptr<OrthographicCameraController> m_CameraController;
	std::unique_ptr<PerspectiveCameraController> m_CameraController;

	std::vector<Engine::GameObject> m_Cubes;

	float m_LastFrameTime = 0;
	int frameCount = 0;
};