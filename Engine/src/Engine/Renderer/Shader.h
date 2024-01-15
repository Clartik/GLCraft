#pragma once

namespace Engine
{
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::string& GetName() const = 0;

		virtual void SetUniformFloat(const std::string& name, float value) = 0;
		virtual void SetUniformInt(const std::string& name, int value) = 0;

		virtual void SetUniformVec2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetUniformVec3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetUniformVec4(const std::string& name, const glm::vec4& value) = 0;

		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) = 0;

		static std::shared_ptr<Shader> Create(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath);
	};
}