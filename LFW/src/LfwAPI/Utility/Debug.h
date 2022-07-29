#pragma once

namespace LFW {

	namespace Debug
	{
		//Takes in a std::string by reference, logs in white text
		void Log(std::string& msg);

		//Takes in a const char*, logs in white text
		void Log(const char* msg);

		//Takes in a std::string by reference & color (0-3)
		void Log(std::string& msg, int clr);

		//Takes in a const char* & color (0-3)
		void Log(const char* msg, int clr);

		//Only call this in BuildUI
		void BuildLogWindow();
	};
}
