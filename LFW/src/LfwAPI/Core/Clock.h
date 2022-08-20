#pragma once
#include "LFWpch.h"
#include "LfwAPI/Core/DeltaTime.h"

namespace LFW {

	//Formats for easier usage when printing elapsed tiume
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
	public:
		Clock();

		//Resets timer, called at construction
		void Reset();

		//Returns elapsed time since object instatiation
		float Elapsed();

		//Returns elapsed time since object instatiation
		float ElapsedMilliSeconds();

		//Prints elapsed time with specified format
		void PrintElapsedTime(const char* format);

		//Resets timer after a certain time har passed
		void ResetAfterSeconds(const int seconds);

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
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