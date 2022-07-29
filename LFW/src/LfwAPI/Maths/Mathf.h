#pragma once

#include "LFWpch.h"

//--------------------------------------------------------------------------
//			WIP - LFW::Mathf Library
//--------------------------------------------------------------------------
/*
	////////////////////////////////// TODO: //////////////////////////////////

	- (IMPLEMENTED) Max 
	- (IMPLEMENTED) Min    
	- (IMPLEMENTED) Sqrt
	- (IMPLEMENTED) PI 9 -11 
	- (IMPLEMENTED) Floor
	- (IMPLEMENTED) Clamp
	- (WIP) Round
	- (WIP) Atan
	- (WIP) Lerp
*/


namespace LFW {

	namespace Mathf {

		// Returns the given value between those numbers. 0 & 5 return 5.
		float Clamp(float min, float max)
		{
			float f;
			f = max - min;

			std::cout << "diff: " << f << "\n";

			return f;
		}

		//Double
		double Sqrt(double value)
		{
			return std::sqrt(value);
		}

		//Float
		float Sqrt(float value)
		{
			return std::sqrt(value);
		}

		//int
		int Sqrt(int value)
		{
			return std::sqrt(value);
		}

		//11 floating numbers
		float PI11()
		{
			return 3.14159265359;
		}

		//9 floating numbers
		float PI9()
		{
			return 3.141592653;
		}

		//7 floating numbers
		float PI()
		{
			return 3.1415926;
		}

		//Returns the largest integer smaller than or equal to f
		int Floor(float value)
		{
			float castedFloatValue = value;
			int floatValueCastedToInteger = (int)castedFloatValue;

			if (value < 0)
			{
				int negativeDifference = castedFloatValue;
				castedFloatValue -= negativeDifference;
				float differenceRounded = negativeDifference - 0.5f;
				float staticCompNumber = negativeDifference + castedFloatValue;

				if (staticCompNumber < differenceRounded)
				{
					//Take base value, cast to int and add -1.
					int negativeFlooredInteger = (int)value - 1;
					std::cout << "Floored negative integer: " << negativeFlooredInteger << "\n";
					return negativeFlooredInteger;
				}

				//Else
				std::cout << "Floored negative integer: " << floatValueCastedToInteger << "\n";
				return floatValueCastedToInteger;
			}
			std::cout << "Floored positive integer: " << floatValueCastedToInteger << "\n";
			return floatValueCastedToInteger;
		}

		//Returns largest of two values
		float Max(float a, float b)
		{
			if (a == b)
			{
				std::cout << "Both values are equal. Returning first value";
				return a;
			}

			if (a > b)
			{
				return a;
			}
			else return b;
		}

		//Returns smallest of two values
		float Min(float a, float b)
		{
			if (a == b)
			{
				std::cout << "Both values are equal. Returning first value";
				return a;
			}

			if (a < b)
			{
				return a;
			}
			else return b;
		}
	}

}
