#pragma once

#include <Engine.h>

#include "Chunk.h"

#include "OrthographicCameraController.h"
#include "PerspectiveCameraController.h"

namespace GLCraft
{
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
		//std::unique_ptr<OrthographicCameraController> m_CameraController;
		std::unique_ptr<PerspectiveCameraController> m_CameraController;

		Chunk* m_Chunk;
		Engine::Mesh m_Square;
		Engine::Mesh m_Cube;

		std::shared_ptr<Engine::Texture2D> m_Texture;

		float m_LastFrameTime = 0;
		int frameCount = 0;
	};
}