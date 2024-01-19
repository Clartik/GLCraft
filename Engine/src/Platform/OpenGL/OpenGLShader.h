#pragma once

#include "Engine/Renderer/Shader.h"

typedef unsigned int GLenum;

namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		inline virtual const std::string& GetName() const override { return m_Name; }

		virtual void SetUniformFloat(const std::string& name, float value) override;
		virtual void SetUniformInt(const std::string& name, int value) override;

		virtual void SetUniformVec2(const std::string& name, const glm::vec2& value) override;
		virtual void SetUniformVec3(const std::string& name, const glm::vec3& value) override;
		virtual void SetUniformVec4(const std::string& name, const glm::vec4& value) override;

		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) override;
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> Preprocess(const std::string & source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		int GetUniformLocation(const std::string& name);
	private:
		unsigned int m_RendererID;

		std::string m_Name;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}