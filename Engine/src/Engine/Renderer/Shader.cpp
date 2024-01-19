#include "pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Engine
{
	/////////////////////////////////////////////////////////////////
	///////////////////////// SHADER ////////////////////////////////
	/////////////////////////////////////////////////////////////////

	std::shared_ptr<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(filepath);
			default:
				break;
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	std::shared_ptr<Shader> Shader::Create(const std::string& name,
										   const std::string& vertexPath, const std::string& fragmentPath)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
			{
				CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			}
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(name, vertexPath, fragmentPath);
			default:
				break;
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	/////////////////////////////////////////////////////////////////
	////////////////////// SHADER LIBRARY ///////////////////////////
	/////////////////////////////////////////////////////////////////

	void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
	{
		CORE_ASSERT(!Exists(name), "Shader Already Exists!");
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
	{
		const std::string& name = shader->GetName();
		Add(name, shader);
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);

		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);

		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
	{
		auto shader = Shader::Create(name, vertexPath, fragmentPath);
		Add(name, shader);

		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name)
	{
		CORE_ASSERT(Exists(name), "Shader Not Found!");
		return m_Shaders[name];
	}
}