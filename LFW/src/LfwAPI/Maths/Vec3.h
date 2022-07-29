#pragma once

#include "LFWpch.h"



namespace LFW {

	struct Vec3
	{
		//X value
		float x;

		//Y value
		float y;

		//Z value
		float z;


		//--------------------------------------------------------------------------
		// Constructors
		//--------------------------------------------------------------------------
		Vec3()
		{
			x = 0;
			y = 0;
			z = 0;
		}
		Vec3(Vec3& const)
		{
		}
		Vec3(float xVal, float yVal)
			: x(xVal), y(yVal)
		{
			z = 0;
		}
		Vec3(float xVal, float yVal, float zVal)
			: x(xVal), y(yVal), z(zVal)
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
		}

		//Subtracts the parameter value to the whole vector
		void Sub(float value)
		{
			x -= value;
			y -= value;
			z -= value;
		}

		//Multiplies the parameter value with the whole vector
		void Mult(float value)
		{
			x* value;
			y* value;
			z* value;
		}

		//Set the parameter value to the whole vector
		void Set(float value)
		{
			x = value;
			y = value;
			z = value;
		}

		//--------------------------------------------------------------------------
		// Vector parameter
		//--------------------------------------------------------------------------

		//Adds the referenced vectors value to our member variables
		void Add(Vec3& vector)
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
		}

		//Subtracts the referenced vectors value to our member variables
		void Sub(Vec3& vector)
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
		}

		//Multiplies the referenced vectors value to our member variables
		void Mult(Vec3& vector)
		{
			x* vector.x;
			y* vector.y;
			z* vector.z;
		}

		//Set the referenced vectors value to our member variables
		void Set(Vec3& vector)
		{
			x = vector.x;
			y = vector.y;
			z = vector.z;
		}

		//Returns the total value of the vector as a string
		std::string ToStringTotal()
		{
			float temp = x + y + z;
			std::string tempTotal = std::to_string(temp);
			return tempTotal;
		}

		//Returns the individual values of the vector as a string
		std::string ToString()
		{
			std::string tempX = std::to_string(x);
			std::string tempY = std::to_string(y);
			std::string tempZ = std::to_string(z);
			return "[" + tempX + ", " + tempY + ", " + tempZ + "]";
		}

		//----------------------------------------------------------------

	};
}