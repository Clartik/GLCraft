#include <Engine/Core/EntryPoint.h>

#include "MainLayer.h"

class GLCraftApp : public Engine::Application
{
public:
	GLCraftApp(const std::string& title)
		: Engine::Application(title)
	{
		PushLayer(new GLCraft::MainLayer);
	}
};

Engine::Application* Engine::CreateApplication()
{
	return new GLCraftApp("GLCraft");
}