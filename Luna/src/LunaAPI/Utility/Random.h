#pragma once
#include "Lunapch.h"

//Does this even work properly?..
namespace Luna {

	//Just to generate!
	class Random
	{

	private:
		static const int MAX_SIZE = 9; //9 is max for stoi to parse...
		static uint64_t m_RandomNumber; //change to uint32_t?
		static std::string m_Numbers;


		//Move below member-fields
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

			//std::cout << tempID << std::endl;
			uint64_t temp = std::stoi(tempID); //change to uint32_t?

			m_RandomNumber = temp;

			//std::cout << "ID: " << m_RandomNumber << std::endl;
			return m_RandomNumber;
		}
	};

}
