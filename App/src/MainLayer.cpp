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
		Engine::RenderCommand::SetCullingMode(Engine::CullingMode::BACK);

		std::shared_ptr<Engine::Shader> shader = Engine::Shader::Create("Basic", 
			"assets/shaders/Texture.vert", "assets/shaders/Texture.frag");

		m_Texture = Engine::Texture2D::Create("assets/textures/KMLOGOPresents.png");

		shader->Bind();
		shader->SetUniformInt("u_Texture", 0);

		m_Chunk = new Chunk({ 0, 0 });
		m_Chunk->GetMesh()->LoadShader(shader);

		std::vector<Engine::Vertex> verts;
		std::vector<unsigned int> indices;

		Engine::Mesh::CreateQuad(verts, indices, glm::vec2(1.0f), { 1, 0, 0, 1 });
		m_Square.LoadVertices(verts.data(), verts.size() * sizeof(Engine::Vertex));
		m_Square.LoadIndices(indices.data(), indices.size());
		m_Square.LoadShader(shader);

		Block block;
		Engine::Vertex* blockVerts = block.GetVertices();
		unsigned int* blockIndices = block.GetIndices();

		m_Cube.LoadVertices(blockVerts, BLOCK_VERTEX_AMOUNT * sizeof(Engine::Vertex));
		m_Cube.LoadIndices(blockIndices, INDEX_AMOUNT_CUBE);
		m_Cube.LoadShader(shader);

		const auto& window = Engine::Application::Get().GetWindow();
		float aspectRatio = (float)window.GetWidth() / (float)window.GetHeight();

		/*m_CameraController = std::make_unique<OrthographicCameraController>(aspectRatio,
			Engine::Transform({0, 0, 1}));*/

		m_CameraController = std::make_unique<PerspectiveCameraController>(45.0f, aspectRatio, 0.1f, 100.0f,
			Engine::Transform(glm::vec3(0.0f, 0, 10.0f)));

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

		m_Texture->Bind();
		Engine::Renderer::BeginScene(m_CameraController->GetCamera());

		//Engine::Renderer::Submit(m_Chunk->GetMesh(), &m_Chunk->GetTransform());
		/*Engine::Transform transform = Engine::Transform();
		Engine::Renderer::Submit(&m_Square, &transform);*/

		Engine::Transform transform2 = Engine::Transform({5, 0, 0});
		Engine::Renderer::Submit(&m_Cube, &transform2);

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
