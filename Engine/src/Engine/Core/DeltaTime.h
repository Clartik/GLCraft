#pragma once

namespace Engine
{
	class DeltaTime
	{
	public:
		DeltaTime(float time)
			: m_Time(time) {}

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 0.001f; }
	private:
		float m_Time;
	};
}