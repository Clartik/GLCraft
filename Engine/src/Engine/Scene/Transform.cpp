#include "pch.h"
#include "Transform.h"

#include <glm/gtx/quaternion.hpp>

namespace Engine
{
	Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
		: m_Position(position), m_RotationEuler(rotation), m_Scale(scale), 
		m_RotationQuat(glm::radians(m_RotationEuler)), m_Matrix(1.0f),
		m_Forward(0.0f, 0.0f, 1.0f), m_Right(1.0f, 0.0f, 0.0f), m_Up(0.0f, 1.0f, 0.0f)
	{
		CalculateMatrix();
	}

	Transform::~Transform()
	{
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		CalculateMatrix();
	}

	void Transform::SetRotation(const glm::vec3& rotation)
	{
		m_RotationEuler = rotation;
		m_RotationQuat = glm::quat(glm::radians(m_RotationEuler));
		CalculateMatrix();
	}

	void Transform::SetRotation(const glm::quat& rotation)
	{
		m_RotationQuat = rotation;
		m_RotationEuler = glm::degrees(glm::eulerAngles(m_RotationQuat));
		CalculateMatrix();
	}

	void Transform::SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		CalculateMatrix();
	}

	void Transform::Move(const glm::vec3& move)
	{
		m_Position += move;
		CalculateMatrix();
	}

	void Transform::Rotate(const glm::vec3& rotate)
	{
		m_RotationEuler += rotate;
		m_RotationQuat = glm::quat(glm::radians(m_RotationEuler));
		CalculateMatrix();
	}

	void Transform::Rotate(float degreees, const glm::vec3& axis)
	{
		m_RotationQuat = glm::angleAxis(degreees, axis);
		CalculateMatrix();
	}

	void Transform::Scale(const glm::vec3& scale)
	{
		m_Scale += scale;
		CalculateMatrix();
	}

	void Transform::SetMatrix(const glm::mat4& matrix)
	{
		m_Matrix = matrix;
		CalculateVectors();

		glm::mat3 scaleMatrix = glm::mat3(m_Matrix);

		glm::vec3 scale;
		scale.x = glm::length(scaleMatrix[0]);
		scale.y = glm::length(scaleMatrix[1]);
		scale.z = glm::length(scaleMatrix[2]);

		m_Scale = scale;

		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix[0][0] = m_Matrix[0][0] / scale.x;
		rotationMatrix[1][0] = m_Matrix[1][0] / scale.x;
		rotationMatrix[2][0] = m_Matrix[2][0] / scale.x;

		rotationMatrix[0][1] = m_Matrix[0][1] / scale.y;
		rotationMatrix[1][1] = m_Matrix[1][1] / scale.y;
		rotationMatrix[2][1] = m_Matrix[2][1] / scale.y;

		rotationMatrix[0][2] = m_Matrix[0][2] / scale.z;
		rotationMatrix[1][2] = m_Matrix[1][2] / scale.z;
		rotationMatrix[2][2] = m_Matrix[2][2] / scale.z;

		m_RotationQuat = glm::quat_cast(rotationMatrix);
		m_RotationEuler = glm::degrees(glm::eulerAngles(m_RotationQuat));
	}

	void Transform::RemoveMatrixUpdateCallback(const MatrixUpdateCallback& callback)
	{
		// TODO
		/*auto it = std::find(m_MatrixUpdateCallbacks.begin(), m_MatrixUpdateCallbacks.end(), callback);

		if (it == m_MatrixUpdateCallbacks.end())
		{
			LOG_WARN("Could Not Remove Matrix Update Callback!");
			return;
		}

		m_MatrixUpdateCallbacks.erase(it);*/
	}

	void Transform::CalculateMatrix()
	{
		m_Matrix = glm::mat4(1.0f);

		m_Matrix *= glm::translate(glm::mat4(1.0f), m_Position);

		m_Matrix *= glm::toMat4(m_RotationQuat);

		m_Matrix *= glm::scale(glm::mat4(1.0f), m_Scale);

		CalculateVectors();
		NotifyMatrixUpdate();
	}

	void Transform::CalculateVectors()
	{
		glm::mat3 rotationMatrix = glm::mat3(m_Matrix);

		m_Right = glm::normalize(rotationMatrix * glm::vec3(1, 0, 0));
		m_Forward = glm::normalize(rotationMatrix * glm::vec3(0, 0, 1));
		m_Up = glm::normalize(rotationMatrix * glm::vec3(0, 1, 0));
	}

	void Transform::NotifyMatrixUpdate()
	{
		for (auto& callback : m_MatrixUpdateCallbacks)
		{
			if (callback)
				callback();
		}
	}
}