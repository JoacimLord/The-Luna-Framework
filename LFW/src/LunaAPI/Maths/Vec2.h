#pragma once

#include "LFWpch.h"

//--------------------------------------------------------------------------
//			WIP - VECTOR2
//--------------------------------------------------------------------------
/*
	////////////////////////////////// TODO: //////////////////////////////////

	- (IMPLEMENTED) Add - For all vector types! (vec2, vec3, vec4)
	- (IMPLEMENTED) Sub
	- (IMPLEMENTED) Set
	- (IMPLEMENTED) Constructors!
	- (IMPLEMENTED) ToString
	- (IMPLEMENTED) ToStringTotal
	- (WIP) Distance
	- (WIP) Lerp
	- (WIP) Max
	- (WIP) Min
	- (WIP) Scale
	- (WIP) Normalize
*/


namespace LFW {

	struct Vec2
	{
		//X value
		float x;

		//Y value
		float y;


		//--------------------------------------------------------------------------
		// Constructors
		//--------------------------------------------------------------------------
		Vec2()
		{
			x = 0;
			y = 0;
		}
		Vec2(Vec2& const)
		{
		}
		Vec2(float xVal, float yVal)
			: x(xVal), y(yVal)
		{
		}


		//--------------------------------------------------------------------------
		// Value parameter
		//--------------------------------------------------------------------------

		//Adds the parameter value to the whole vector
		void Add(float value)
		{
			x += value;
			y += value;
		}

		//Subtracts the parameter value to the whole vector
		void Sub(float value)
		{
			x -= value;
			y -= value;
		}

		//Multiplies the parameter value with the whole vector
		void Mult(float value)
		{
			x* value;
			y* value;
		}

		//Set the parameter value to the whole vector
		void Set(float value)
		{
			x = value;
			y = value;
		}

		//--------------------------------------------------------------------------
		// Vector parameter
		//--------------------------------------------------------------------------

		//Adds the referenced vectors value to our member variables
		void Add(Vec2& vector)
		{
			x += vector.x;
			y += vector.y;
		}

		//Subtracts the referenced vectors value to our member variables
		void Sub(Vec2& vector)
		{
			x -= vector.x;
			y -= vector.y;
		}

		//Multiplies the referenced vectors value to our member variables
		void Mult(Vec2& vector)
		{
			x* vector.x;
			y* vector.y;
		}

		//Set the referenced vectors value to our member variables
		void Set(Vec2& vector)
		{
			x = vector.x;
			y = vector.y;
		}


		//Returns the total value of the vector as a string
		std::string ToStringTotal()
		{
			float temp = x + y;
			std::string tempTotal = std::to_string(temp);
			return tempTotal;
		}

		//Returns the individual values of the vector as a string
		std::string ToString()
		{
			std::string tempX = std::to_string(x);
			std::string tempY = std::to_string(y);
			return "[" + tempX + ", " + tempY + "]";
		}
	};
}

