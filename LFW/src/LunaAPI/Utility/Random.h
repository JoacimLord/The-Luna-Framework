#pragma once
#include "LFWpch.h"

namespace LFW {

	class Random
	{
	private:
		Random() = default;

	public:
		static uint64_t GenerateRandomNumber() //change to uint32_t?
		{
			std::string tempID = "";

			for (int i = 0; i < MAX_SIZE; i++)
			{
				char tempNumber = std::rand() % 9;
				tempID += m_Numbers[tempNumber];
			}

			uint64_t temp = std::stoi(tempID); //change to uint32_t?
			m_RandomNumber = temp;
			return m_RandomNumber;
		}

	private:
		static const int MAX_SIZE = 9; //9 is max for stoi to parse...
		static uint64_t m_RandomNumber; //change to uint32_t?
		static std::string m_Numbers;
	};

}

//Random Device
/*
			static std::random_device random;
			static std::mt19937_64 generator(random());
			static std::uniform_int_distribution<> valueRange(0, 15);

			for (int i = 0; i < 32; i++)
			{
				temp = valueRange(generator);
				UUID += characters[temp];

				//Add '-' between each block of characters

				if (UUID.size() == 8) UUID.append("-");
				else if (UUID.size() == 13) UUID.append("-");
				else if (UUID.size() == 18) UUID.append("-");
				else if (UUID.size() == 23) UUID.append("-");
			}
*/
