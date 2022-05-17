#pragma once
#include "Lunapch.h"
#include "LunaAPI/Core/DeltaTime.h"

namespace Luna {

	namespace ClockFormats
	{
		const char* ZERO_DECIMAL = "%.0f";
		const char* ONE_DECIMAL = "%.1f";
		const char* TWO_DECIMAL = "%.2f";
		const char* THREE_DECIMAL = "%.3f";
		const char* FOUR_DECIMAL = "%.4f";
		const char* FIVE_DECIMAL = "%.5f";
	}

	class Clock
	{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;

	public:
		Clock();

		void Reset();
		float Elapsed();
		float ElapsedMilliSeconds();
		void PrintElapsedTime(const char* format);
		void ResetAfterSeconds(const int seconds);
	};

	Clock::Clock()
	{
		Reset();
	}

	void Clock::Reset()
	{
		m_Start = std::chrono::high_resolution_clock::now();
	}

	float Clock::Elapsed()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
	}

	float Clock::ElapsedMilliSeconds()
	{
		return Elapsed() * 1000.0f;
	}

	void Clock::PrintElapsedTime(const char* format)
	{
		float temporary = Elapsed();

		printf(format, temporary);
		std::cout << "\n";
	}

	void Clock::ResetAfterSeconds(const int seconds)
	{
		if ((int)Elapsed() >= seconds)
		{
			std::cout << "Timer reached " << seconds << " seconds elapsed, resetting!\n";
			Reset();
		}
	}
}