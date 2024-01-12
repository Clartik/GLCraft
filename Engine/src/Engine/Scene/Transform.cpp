#include "pch.h"
#include "Transform.h"

namespace Engine
{
	Transform::Transform(const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
		: m_Position(position), m_Rotation(rotation), m_Scale(scale), m_Matrix(1.0f),
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
		m_Rotation = rotation;

		/*if (int(rotation.x) / 360 > 0)
			m_Rotation.x = rotation.x / 360.0f;

		if (int(rotation.y) / 360 > 0)
			m_Rotation.y = rotation.y / 360.0f;

		if (int(rotation.z) / 360 > 0)
			m_Rotation.z = rotation.z / 360.0f;*/

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
		m_Rotation += rotate;
		CalculateMatrix();
	}

	void Transform::Rotate(float degreees, const glm::vec3& axis)
	{
		m_Rotation += degreees * axis;
		CalculateMatrix();
	}

	void Transform::Scale(const glm::vec3& scale)
	{
		m_Scale += scale;
		CalculateMatrix();
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

		m_Matrix *= glm::scale(glm::mat4(1.0f), m_Scale);

		m_Matrix *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		m_Matrix *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		m_Matrix *= glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		m_Matrix *= glm::translate(glm::mat4(1.0f), m_Position);

		CalculateVectors();
		NotifyMatrixUpdate();
	}

	void Transform::CalculateVectors()
	{
		m_Right = glm::vec3(m_Matrix[0]);
		m_Forward = glm::vec3(m_Matrix[2]);
		m_Up = glm::cross(m_Forward, m_Right);
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