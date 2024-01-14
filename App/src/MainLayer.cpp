#include "MainLayer.h"

#include "Engine/Renderer/Renderer.h"
#include "Engine/Core/Time.h"

MainLayer::MainLayer()
	: Layer("Main Layer")
{
	Engine::RenderCommand::ShowDepth(true);

	std::vector<Engine::Vertex> cubeVerts;

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

	m_Shader = Engine::Shader::Create("Basic", "assets/shaders/Basic.vert", "assets/shaders/Basic.frag");

	for (int height = -64; height < 0; height++)
	{
		for (int row = 0; row < 16; row++)
		{
			for (int column = 0; column < 16; column++)
			{
				Engine::GameObject cube(Engine::Transform({ row, height, column }));
				Engine::Mesh& cubeMesh = cube.GetMesh();

				cubeVerts.clear();
				float red, green;

				if (row % 2)
				{
					red = 1.0f;
					green = 0;
				}
				else
				{
					green = 1.0f;
					red = 0;
				}

				Engine::Mesh::CreateCube(cubeVerts, glm::vec3(0.5f), glm::vec4(red, green, 0, 1));

				cubeMesh.LoadVertices(cubeVerts.data(), 8 * sizeof(Engine::Vertex));
				cubeMesh.LoadIndices(cubeIndices, sizeof(cubeIndices));
				cubeMesh.LoadShader(m_Shader);

				m_Cubes.push_back(cube);
			}
		}
	}

	const auto& window = Engine::Application::Get().GetWindow();
	float aspectRatio = (float)window.GetWidth() / (float)window.GetHeight();

	/*m_CameraController = std::make_unique<OrthographicCameraController>(aspectRatio, 
		Engine::Transform({0, 0, 1}));*/

	m_CameraController = std::make_unique<PerspectiveCameraController>(45.0f, aspectRatio, 0.1f, 100.0f, 
		Engine::Transform(glm::vec3(0.0f, 0.0f, -1.0f)));

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

	//Engine::Renderer::BeginScene(*m_Camera);
	Engine::Renderer::BeginScene(m_CameraController->GetCamera());

	for (auto& cube : m_Cubes)
		Engine::Renderer::Submit(&cube);

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
