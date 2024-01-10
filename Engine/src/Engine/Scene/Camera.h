#pragma once

namespace Engine
{
	class Camera
	{
	public:
		virtual const glm::vec3& GetPosition() const = 0;
		virtual const float& GetRotation() const = 0;

		virtual void SetPosition(const glm::vec3& position) = 0;
		virtual void SetRotation(float rotation) = 0;

		virtual const glm::mat4& GetProjection() const = 0;
		virtual const glm::mat4& GetView() const = 0;
		virtual const glm::mat4& GetViewProjection() const = 0;
	private:
		virtual void RecalculateView() = 0;
	};
}