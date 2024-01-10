#include "MainLayer.h"

#include "Engine/Renderer/Renderer.h"

MainLayer::MainLayer()
	: Layer("Main Layer")
{
	m_VAO = Engine::VertexArray::Create();

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};

	auto vertexBuffer = Engine::VertexBuffer::Create(vertices, sizeof(vertices));
	Engine::BufferLayout layout = {
		{ Engine::ShaderDataType::Float3, "pos" },
		{ Engine::ShaderDataType::Float4, "color" }
	};

	vertexBuffer->SetLayout(layout);
	m_VAO->AddVertexBuffer(vertexBuffer);

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	auto indexBuffer = Engine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(unsigned int));
	m_VAO->SetIndexBuffer(indexBuffer);

	m_Shader = Engine::Shader::Create("Basic", "assets/shaders/Basic.vert", "assets/shaders/Basic.frag");

	const auto& window = Engine::Application::Get().GetWindow();
	/*Engine::PerspectiveCamera::ProjDetails projDetails(45.0f, (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);
	m_Camera = std::make_shared<Engine::PerspectiveCamera>(projDetails, glm::vec3(0.0f, 0.0f, -5.0f), 
		glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/

	float aspectRatio = (float)window.GetWidth() / (float)window.GetHeight();
	Engine::OrthographicCamera::ProjectionDetails projDetails(aspectRatio, -1.0f, 1.0f, -1.0f, 1.0f);
	m_Camera = std::make_shared<Engine::OrthographicCamera>(projDetails, glm::vec3(0.0f, 0.0f, 0.0f));
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

	Engine::Renderer::BeginScene(*m_Camera);

	Engine::Renderer::Submit(m_Shader, m_VAO);

	Engine::Renderer::EndScene();
}

void MainLayer::OnEvent(Engine::Event& e)
{
}
