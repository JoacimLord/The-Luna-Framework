#pragma once

#include "LFWpch.h"


namespace LFW {

	struct Vec4
	{
		//X value
		float x;

		//Y value
		float y;

		//Z value
		float z;

		//W value
		float w;

		//--------------------------------------------------------------------------
		// Constructors
		//--------------------------------------------------------------------------
		Vec4()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}
		Vec4(Vec4& const)
		{
		}
		Vec4(float xVal, float yVal)
			: x(xVal), y(yVal)
		{
			z = 0;
			w = 0;
		}
		Vec4(float xVal, float yVal, float zVal)
			: x(xVal), y(yVal), z(zVal)
		{
			w = 0;
		}
		Vec4(float xVal, float yVal, float zVal, float wVal)
			: x(xVal), y(yVal), z(zVal), w(wVal)
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
			z += value;
			w += value;
		}

		//Subtracts the parameter value to the whole vector
		void Sub(float value)
		{
			x -= value;
			y -= value;
			z -= value;
			w -= value;
		}

		//Multiplies the parameter value with the whole vector
		void Mult(float value)
		{
			x* value;
			y* value;
			z* value;
			w* value;
		}

		//Set the parameter value to the whole vector
		void Set(float value)
		{
			x = value;
			y = value;
			z = value;
			w = value;
		}

		//--------------------------------------------------------------------------
		// Vector parameter
		//--------------------------------------------------------------------------

		//Adds the referenced vectors value to our member variables
		void Add(Vec4& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			w += vector.w;
		}

		//Subtracts the referenced vectors value to our member variables
		void Sub(Vec4& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			w -= vector.w;
		}

		//Multiplies the referenced vectors value to our member variables
		void Mult(Vec4& vector)
		{
			x* vector.x;
			y* vector.y;
			z* vector.z;
			w* vector.w;
		}

		//Set the referenced vectors value to our member variables
		void Set(Vec4& vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
			w = vector.w;
		}

		//Returns the total value of the vector as a string
		std::string ToStringTotal()
		{
			float temp = x + y + z + w;
			std::string tempTotal = std::to_string(temp);
			return tempTotal;
		}

		//Returns the individual values of the vector as a string
		std::string ToString()
		{
			std::string tempX = std::to_string(x);
			std::string tempY = std::to_string(y);
			std::string tempZ = std::to_string(z);
			std::string tempW = std::to_string(w);
			return "[" + tempX + ", " + tempY + ", " + tempZ + ", " + tempW + "]";
		}
	};
}
