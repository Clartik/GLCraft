#pragma once

#include "Transform.h"
#include "Mesh.h"

namespace Engine
{
	class GameObject
	{
	public:
		GameObject(const Transform& transform)
			: m_Transform(transform) {}
		~GameObject() {}
		
		inline Transform& GetTransform() { return m_Transform; }
		inline Mesh& GetMesh() { return m_Mesh; }
	private:
		Transform m_Transform;
		Mesh m_Mesh;
	};
}