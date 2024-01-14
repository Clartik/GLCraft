#pragma once

#include <Engine.h>

#include "Block.h"

#include "OrthographicCameraController.h"
#include "PerspectiveCameraController.h"

namespace GLCraft
{
	const unsigned int CHUNK_HEIGHT = 64, CHUNK_ROWS = 16, CHUNK_COLUMNS = 16;

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

		std::array<std::array<std::array<Block, CHUNK_COLUMNS>, CHUNK_ROWS>, CHUNK_HEIGHT> m_Chunk;
		Engine::Mesh m_ChunkMesh;

		float m_LastFrameTime = 0;
		int frameCount = 0;
	};
}