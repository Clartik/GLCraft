#include "MainLayer.h"

#include <Engine/Renderer/Renderer.h>

namespace GLCraft
{
	MainLayer::MainLayer()
		: Layer("Main Layer")
	{
		Engine::RenderCommand::ShowDepth(true);
		Engine::RenderCommand::SetCullingMode(Engine::CullingMode::BACK);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		auto basicShader = m_ShaderLibrary.Load("Basic", "assets/shaders/Basic.vert", "assets/shaders/Basic.frag");

		textureShader->Bind();
		textureShader->SetUniformInt("u_Texture", 0);

		m_TextureAtlas = Engine::Texture2D::Create("assets/textures/Blocks.png");

		m_Chunk = new Chunk({ 0, 0, 0 });
		m_Chunk->GetMesh()->LoadShader(textureShader);

		const auto& window = Engine::Application::Get().GetWindow();
		float aspectRatio = (float)window.GetWidth() / (float)window.GetHeight();

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
		
		Engine::Renderer::BeginScene(m_CameraController->GetCamera());

		m_TextureAtlas->Bind();
		Engine::Renderer::Submit(m_Chunk->GetMesh(), &m_Chunk->GetTransform());

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
