#include "MainLayer.h"

#include "Engine/Renderer/Renderer.h"

namespace GLCraft
{
	void AddFace(std::vector<Engine::Vertex>& chunkVertices, std::vector<unsigned int>& chunkIndices,
		const glm::vec3& location, Engine::Vertex* vertices, int& chunkVertexIndex)
	{
		for (int i = 0; i < VERTEX_AMOUNT_QUAD; i++)
		{
			vertices[i].Position += location;
			chunkVertices.push_back(vertices[i]);
		}

		chunkIndices.push_back(chunkVertexIndex);
		chunkIndices.push_back(chunkVertexIndex + 1);
		chunkIndices.push_back(chunkVertexIndex + 2);
		chunkIndices.push_back(chunkVertexIndex + 2);
		chunkIndices.push_back(chunkVertexIndex + 3);
		chunkIndices.push_back(chunkVertexIndex);
		chunkVertexIndex += VERTEX_AMOUNT_QUAD;
	}

	MainLayer::MainLayer()
		: Layer("Main Layer")
	{
		Engine::RenderCommand::ShowDepth(true);
		Engine::RenderCommand::SetWindingOrder(false);
		Engine::RenderCommand::SetCullingMode(Engine::CullingMode::BACK);

		std::shared_ptr<Engine::Shader> shader = Engine::Shader::Create("Basic", "assets/shaders/Basic.vert", "assets/shaders/Basic.frag");

		std::vector<Engine::Vertex> chunkVertices;
		std::vector<unsigned int> chunkIndices;

		int chunkVertexIndex = 0;

		for (int height = 0; height < CHUNK_HEIGHT; height++)
		{
			for (int row = 0; row < CHUNK_ROWS; row++)
			{
				for (int column = 0; column < CHUNK_COLUMNS; column++)
				{
					Block block(Engine::Transform({ row, height, column }));
					m_Chunk[height][row][column] = block;
				}
			}
		}

		for (int height = 0; height < CHUNK_HEIGHT; height++)
		{
			for (int row = 0; row < CHUNK_ROWS; row++)
			{
				for (int column = 0; column < CHUNK_COLUMNS; column++)
				{
					Block& block = m_Chunk[height][row][column];

					if (row - 1 < 0)
					{
						Engine::Vertex* vertices = block.GetFace(BlockFaceType::RIGHT);
						glm::vec3 location = { row, height, column };
						AddFace(chunkVertices, chunkIndices, location, vertices, chunkVertexIndex);
					}

					if (row + 1 > CHUNK_ROWS - 1)
					{
						Engine::Vertex* vertices = block.GetFace(BlockFaceType::LEFT);
						glm::vec3 location = { row, height, column };
						AddFace(chunkVertices, chunkIndices, location, vertices, chunkVertexIndex);
					}

					if (column - 1 < 0)
					{
						Engine::Vertex* vertices = block.GetFace(BlockFaceType::FRONT);
						glm::vec3 location = { row, height, column };
						AddFace(chunkVertices, chunkIndices, location, vertices, chunkVertexIndex);
					}

					if (column + 1 > CHUNK_COLUMNS - 1)
					{
						Engine::Vertex* vertices = block.GetFace(BlockFaceType::BACK);
						glm::vec3 location = { row, height, column };
						AddFace(chunkVertices, chunkIndices, location, vertices, chunkVertexIndex);
					}

					if (height - 1 < 0)
					{
						Engine::Vertex* vertices = block.GetFace(BlockFaceType::BOTTOM);
						glm::vec3 location = { row, height, column };
						AddFace(chunkVertices, chunkIndices, location, vertices, chunkVertexIndex);
					}

					if (height + 1 > CHUNK_HEIGHT - 1)
					{
						Engine::Vertex* vertices = block.GetFace(BlockFaceType::TOP);
						glm::vec3 location = { row, height, column };
						AddFace(chunkVertices, chunkIndices, location, vertices, chunkVertexIndex);
					}
				}
			}
		}

		m_ChunkMesh.LoadVertices(chunkVertices.data(), sizeof(Engine::Vertex) * chunkVertices.size());
		m_ChunkMesh.LoadIndices(chunkIndices.data(), chunkIndices.size());
		m_ChunkMesh.LoadShader(shader);

		const auto& window = Engine::Application::Get().GetWindow();
		float aspectRatio = (float)window.GetWidth() / (float)window.GetHeight();

		/*m_CameraController = std::make_unique<OrthographicCameraController>(aspectRatio,
			Engine::Transform({0, 0, 1}));*/

		m_CameraController = std::make_unique<PerspectiveCameraController>(45.0f, aspectRatio, 0.1f, 100.0f,
			Engine::Transform(glm::vec3(0.0f, 65, -5.0f)));

		Engine::Camera& camera = m_CameraController->GetCamera();
		camera.LookAt(glm::vec3(0.0f));
	}

	MainLayer::~MainLayer()
	{
	}

	void MainLayer::OnAttach()
	{
	}

	void MainLayer::OnDetach()
	{
	}

	void MainLayer::OnUpdate(Engine::DeltaTime deltaTime)
	{
		Engine::RenderCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1.0f });
		Engine::RenderCommand::Clear();

		int fps = 1.0f / deltaTime;
		LOG_INFO("FPS: {0}", fps);

		m_CameraController->OnUpdate(deltaTime);

		Engine::Renderer::BeginScene(m_CameraController->GetCamera());

		Engine::Transform transform = Engine::Transform();
		Engine::Renderer::Submit(&m_ChunkMesh, &transform);

		Engine::Renderer::EndScene();

		if (Engine::Input::IsKeyPressed(Engine::Key::F))
		{
			m_CameraController->GetCamera().GetTransform().SetPosition(glm::vec3(0, 0, 1));
			m_CameraController->GetCamera().GetTransform().SetRotation(glm::vec3(0));
		}
	}

	void MainLayer::OnEvent(Engine::Event& e)
	{
		//m_CameraController->OnEvent(e);
	}
}
