#include <Engine.h>
#include <Engine/Core/EntryPoint.h>

class GLCraftApp : public Engine::Application
{
public:
	GLCraftApp(const std::string& title)
		: Engine::Application(title)
	{
		//PushLayer();
	}
};

Engine::Application* Engine::CreateApplication()
{
	return new GLCraftApp("GLCraft");
}