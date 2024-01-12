#pragma once

#include "Transform.h"

namespace Engine
{
	class Camera
	{
	public:
		virtual void LookAt(const glm::vec3& lookAt) = 0;

		virtual Transform& GetTransform() = 0;

		virtual const glm::mat4& GetProjection() const = 0;
		virtual const glm::mat4& GetView() const = 0;
		virtual const glm::mat4& GetViewProjection() const = 0;
	private:
		virtual void SetProjection() = 0;
		virtual void CalculateViewProjection() = 0;
	};
}