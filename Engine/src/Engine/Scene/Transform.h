#pragma once

#include <glm/gtc/quaternion.hpp>

namespace Engine
{
	class Transform
	{
	public:
		using MatrixUpdateCallback = std::function<void()>;
	public:
		Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
		~Transform();

		void SetPosition(const glm::vec3& position);
		void SetRotation(const glm::vec3& rotation);
		void SetScale(const glm::vec3& scale);

		void Move(const glm::vec3& move);
		void Rotate(const glm::vec3& rotate);
		void Rotate(float degreees, const glm::vec3& axis);
		void Scale(const glm::vec3& scale);

		void SetMatrix(const glm::mat4& matrix);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline const glm::vec3& GetEulerRotation() const { return m_RotationEuler; }
		inline const glm::quat& GetQuaternionRotation() const { return m_RotationQuat; }
		inline const glm::vec3& GetScale() const { return m_Scale; }

		inline const glm::mat4& GetMatrix() const { return m_Matrix; }

		inline const glm::vec3& GetForward() const { return m_Forward; }
		inline const glm::vec3& GetRight() const { return m_Right; }
		inline const glm::vec3& GetUp() const { return m_Up; }

		inline void AddMatrixUpdateCallback(const MatrixUpdateCallback& callback) { m_MatrixUpdateCallbacks.push_back(callback); }
		void RemoveMatrixUpdateCallback(const MatrixUpdateCallback& callback);
	private:
		void CalculateMatrix();
		void CalculateVectors();
		void NotifyMatrixUpdate();
	private:
		glm::vec3 m_Position, m_RotationEuler, m_Scale;
		glm::quat m_RotationQuat;
		glm::mat4 m_Matrix;

		glm::vec3 m_Forward, m_Right, m_Up;

		std::vector<MatrixUpdateCallback> m_MatrixUpdateCallbacks;
	};
}