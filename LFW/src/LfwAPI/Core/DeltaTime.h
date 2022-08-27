#pragma once

#include "LFWpch.h"

namespace LFW {

	class DeltaTime
	{
	public:
		DeltaTime(float deltaTime)
			: m_time(deltaTime) {}

		operator float() const { return m_time; }

		//Return time
		float GetSeconds() const { return m_time; }

		//Return time in ms
		float GetMilliSeconds() const { return m_time * 1000.0f; } //seconds * 1000 (milli)

	private:
		float m_time;
	};
}