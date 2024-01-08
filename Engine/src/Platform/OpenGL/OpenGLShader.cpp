#include "pch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>

#include <fstream>

namespace Engine
{
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
		: m_Name(name), m_VertexPath(vertexPath), m_FragmentPath(fragmentPath)
	{
		std::string vertexSrc = ParseShader(vertexPath);
		unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSrc);
		if (!IsCompiled(vertexShader, "Vertex Shader Compilation Failed!")) return;

		std::string fragmentSrc = ParseShader(fragmentPath);
		unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);
		if (!IsCompiled(fragmentShader, "Fragment Shader Compilation Failed!")) return;

		m_RendererID = CreateProgram(vertexShader, fragmentShader);

		if (!IsLinked())
		{
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
	}

	std::string OpenGLShader::ParseShader(const std::string& filepath)
	{
		std::ifstream file(filepath);

		CORE_ASSERT(file, "Error Reading Shader Filepath: {0}", filepath);

		std::stringstream ss;

		ss << file.rdbuf();
		return ss.str();
	}

	unsigned int OpenGLShader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int shader = glCreateShader(type);

		const GLchar* glCharSrc = source.c_str();
		glShaderSource(shader, 1, &glCharSrc, 0);

		glCompileShader(shader);

		return shader;
	}

	bool OpenGLShader::IsCompiled(unsigned int shader, const std::string& errorMsg)
	{
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (compiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			CORE_LOG_ERROR("{0}", infoLog.data());
			CORE_ASSERT(false, errorMsg);

			return false;
		}

		return false;
	}

	bool OpenGLShader::IsLinked()
	{
		GLint linked = 0;
		glGetShaderiv(m_RendererID, GL_COMPILE_STATUS, &linked);

		if (linked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(m_RendererID);

			CORE_LOG_ERROR("{0}", infoLog.data());
			CORE_ASSERT(false, "Shader Linking Failure!");

			return false;
		}

		return false;
	}

	int OpenGLShader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int location = glGetUniformLocation(m_RendererID, name.c_str());

		if (location == -1)
			CORE_LOG_WARN("Uniform '{0}' doesn't exist!", name);

		m_UniformLocationCache[name] = location;
		return location;
	}

	unsigned int OpenGLShader::CreateProgram(unsigned int vertexShader, unsigned int fragmentShader)
	{
		unsigned int program = glCreateProgram();

		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		return program;
	}
}