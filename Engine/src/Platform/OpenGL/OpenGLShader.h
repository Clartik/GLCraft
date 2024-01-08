#pragma once

#include "Engine/Renderer/Shader.h"

namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		inline const std::string& GetName() const { return m_Name; }

		void SetUniformMat4(const std::string& name, const glm::mat4& value) override;
	private:
		std::string ParseShader(const std::string& filepath);
		unsigned int CompileShader(unsigned int type, const std::string& source);
		unsigned int CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);

		bool IsCompiled(unsigned int shader, const std::string& errorMsg);
		bool IsLinked();

		int GetUniformLocation(const std::string& name);
	private:
		unsigned int m_RendererID;
		std::string m_Name;

		std::string m_VertexPath, m_FragmentPath;

		std::unordered_map<std::string, int> m_UniformLocationCache;
	};
}