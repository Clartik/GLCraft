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
		Engine::ShaderLibrary m_ShaderLibrary;
		std::unique_ptr<PerspectiveCameraController> m_CameraController;

		std::shared_ptr<Engine::Texture2D> m_TextureAtlas;

		Chunk* m_Chunk;
	};
}