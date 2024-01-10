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
	float aspectRatio = (float)window.GetWidth() / (float)window.GetHeight();

	//m_Camera = std::make_shared<Engine::PerspectiveCamera>(45.0f, aspectRatio, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, -3.0f));
	//m_Camera->LookAt(glm::vec3(0.0f));

	/*m_CameraController = std::make_unique<OrthographicCameraController>(aspectRatio, glm::vec3(0.0f, 0.0f, -1.0f));
	Engine::Camera& camera = m_CameraController->GetCamera();
	camera.LookAt(glm::vec3(0.0f));*/

	m_CameraController = std::make_unique<PerspectiveCameraController>(45.0f, aspectRatio, 0.1f, 100.0f, glm::vec3(0.0f, 0.0f, 3.0f));
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

	m_CameraController->OnUpdate(deltaTime);

	//Engine::Renderer::BeginScene(*m_Camera);
	Engine::Renderer::BeginScene(m_CameraController->GetCamera());

	Engine::Renderer::Submit(m_Shader, m_VAO);

	Engine::Renderer::EndScene();
}

void MainLayer::OnEvent(Engine::Event& e)
{
	m_CameraController->OnEvent(e);
}
