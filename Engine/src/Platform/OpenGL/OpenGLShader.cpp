#include "pch.h"
#include "OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <filesystem>

namespace Engine
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")	
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		CORE_ASSERT(false, "Unknown Shader Type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string source = ReadFile(filepath);
		auto shaderSources = Preprocess(source);
		Compile(shaderSources);

		std::filesystem::path path = filepath;
		m_Name = path.stem().string();			// Returns the file's name stripped of the extension
	}

	OpenGLShader::OpenGLShader(const std::string& name,
							   const std::string& vertexPath, const std::string& fragmentPath)
		: m_Name(name)
	{
		std::unordered_map<GLenum, std::string> sources;

		sources[GL_VERTEX_SHADER] = ReadFile(vertexPath);
		sources[GL_FRAGMENT_SHADER] = ReadFile(fragmentPath);

		Compile(sources);
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

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string result;
		std::ifstream stream(filepath, std::ios::in | std::ios::binary);

		if (!stream)
		{
			CORE_LOG_ERROR("Could not open file '{0}'", filepath);
			return result;
		}

		stream.seekg(0, std::ios::end);
		result.resize(stream.tellg());

		stream.seekg(0, std::ios::beg);
		stream.read(&result[0], result.size());

		stream.close();
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::Preprocess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);

		while (pos != std::string::npos)
		{
			size_t endOfLine = source.find_first_of("\r\n", pos);
			CORE_ASSERT(endOfLine != std::string::npos, "Syntax Error!");

			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, endOfLine - begin);

			CORE_ASSERT(ShaderTypeFromString(type), "Invalid Shader Type Specified!");

			size_t nextLinePos = source.find_first_not_of("\r\n", endOfLine);
			pos = source.find(typeToken, nextLinePos);

			size_t endOfShaderType = nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos;

			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - endOfShaderType);
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
	{
		GLuint program = glCreateProgram();

		CORE_ASSERT(shaderSources.size() <= 2, "Only 2 Shaders are Supported Currently!");
		std::array<GLenum, 2> glShaderIDs;

		int glShaderIDIndex = 0;
		for (auto& key : shaderSources)
		{
			GLenum type = key.first;
			const std::string& source = key.second;

			GLuint shader = glCreateShader(type);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

			if (!isCompiled)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				CORE_LOG_ERROR("{0}", infoLog.data());
				CORE_ASSERT(false, "Shader Compilation Failure!");

				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		
		if (!isLinked)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(program);

			for (auto& id : glShaderIDs)
				glDeleteShader(id);

			CORE_LOG_ERROR("{0}", infoLog.data());
			CORE_ASSERT(false, "Shader Link Failure!");
			return;
		}

		for (auto& id : glShaderIDs)
			glDetachShader(program, id);

		m_RendererID = program;
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

	void OpenGLShader::SetUniformFloat(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void OpenGLShader::SetUniformVec2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void OpenGLShader::SetUniformVec3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void OpenGLShader::SetUniformVec4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}
}