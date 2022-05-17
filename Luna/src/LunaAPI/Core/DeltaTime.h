#pragma once

#include "Lunapch.h"

namespace Luna {

	class DeltaTime
	{
	private:
		float m_Time;

	public:
		DeltaTime(float deltaTime)
			: m_Time(deltaTime) {}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliSeconds() const { return m_Time * 1000.0f; } //seconds * 1000 (milli)
	};
}