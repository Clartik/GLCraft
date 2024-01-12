#include "MainLayer.h"

#include "Engine/Renderer/Renderer.h"

MainLayer::MainLayer()
	: Layer("Main Layer"), m_Transform(glm::vec3(0.0f), glm::vec3(0), glm::vec3(1)),
	m_TransformCube(glm::vec3(2.0f, 0.0f, 0.0f), glm::vec3(0), glm::vec3(1))
{
	m_VAO = Engine::VertexArray::Create();
	m_VA = Engine::VertexArray::Create();

	float quadVertices[] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	};

	float cubeVertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f,

		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
	};

	auto vertexBuffer = Engine::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
	auto vertexBufferCube = Engine::VertexBuffer::Create(cubeVertices, sizeof(cubeVertices));
	Engine::BufferLayout layout = {
		{ Engine::ShaderDataType::Float3, "pos" },
		{ Engine::ShaderDataType::Float4, "color" }
	};

	vertexBuffer->SetLayout(layout);
	vertexBufferCube->SetLayout(layout);
	m_VAO->AddVertexBuffer(vertexBuffer);
	m_VA->AddVertexBuffer(vertexBufferCube);

	unsigned int quadIndices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int cubeIndices[] = {
		// FRONT
		0, 1, 2,
		2, 3, 0,

		// RIGHT
		4, 0, 3,
		3, 7, 4,

		// BACK
		4, 5, 6,
		6, 7, 4,

		// LEFT
		1, 5, 6,
		6, 2, 1,

		// TOP
		3, 2, 6,
		6, 7, 3,

		// BOTTOM
		4, 5, 1,
		1, 0, 4
	};

	auto indexBuffer = Engine::IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(unsigned int));
	auto indexBufferCube = Engine::IndexBuffer::Create(cubeIndices, sizeof(cubeIndices) / sizeof(unsigned int));
	m_VAO->SetIndexBuffer(indexBuffer);
	m_VA->SetIndexBuffer(indexBufferCube);

	m_Shader = Engine::Shader::Create("Basic", "assets/shaders/Basic.vert", "assets/shaders/Basic.frag");

	const auto& window = Engine::Application::Get().GetWindow();
	float aspectRatio = (float)window.GetWidth() / (float)window.GetHeight();

	/*m_CameraController = std::make_unique<OrthographicCameraController>(aspectRatio, glm::vec3(0.0f, 0.0f, -1.0f));
	Engine::Camera& camera = m_CameraController->GetCamera();
	camera.LookAt(glm::vec3(0.0f));*/

	m_CameraController = std::make_unique<PerspectiveCameraController>(45.0f, aspectRatio, 0.1f, 100.0f, 
		Engine::Transform(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f), glm::vec3(1.0f)));
	Engine::Camera& camera = m_CameraController->GetCamera();
	camera.LookAt(glm::vec3(0.0f));

	Engine::RenderCommand::SetDepth(true);
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

	Engine::Renderer::Submit(m_Shader, m_VAO, m_Transform);
	Engine::Renderer::Submit(m_Shader, m_VA, m_TransformCube);

	Engine::Renderer::EndScene();

	if (Engine::Input::IsKeyPressed(Engine::Key::F))
	{
		m_CameraController->GetCamera().GetTransform().SetPosition(glm::vec3(0, 0, 1));
		m_CameraController->GetCamera().GetTransform().SetRotation(glm::vec3(0));
	}
}

void MainLayer::OnEvent(Engine::Event& e)
{
	m_CameraController->OnEvent(e);
}
