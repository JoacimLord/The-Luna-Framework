#pragma once

//#include "LFWpch.h"
#include "Anchor.h"
#include "LfwAPI/Renderer/Texture.h"
#include "LfwAPI/Core/Defines.h"

namespace LFW {

	struct Sprite
	{
		//Default constructor
		Sprite() = default;

		//Sets the sprites position and size at construction
		Sprite(glm::vec2 position, glm::vec2 size);

		//The sprites placement and orientation in the world.
		//The anchor is a basic matrix with position, scale and rotation (transform).
		Anchor anchor;

		//Adds a texture to the sprite. Load the texture with a filePath and "SetTexture()"
		AddTexture texture;

		//The filepath to the sprites texture
		std::string filePath = "";

		//The color of the sprite. 
		//Default value is 0.
		glm::vec4 color = glm::vec4(0.0f);

		//Sets and loads a texture for the sprite. Use the filePath variable or write the filepath in the function argument
		void SetTexture(std::string path);

		//Sets the position of the sprite in 2D space (x, y)
		void SetPosition(float x, float y);

		//Sets the size of the sprite in 2D space (x, y)
		void SetSize(float w, float h);

		//Sets the rotation of the sprite in 2D space (x axis)
		void SetRotationX(float rotation);

		//Sets the rotation of the sprite in 2D space (y axis)
		void SetRotationY(float rotation);

		//Sets the rotation of the sprite in 2D space (z axis)
		void SetRotationZ(float rotation);
	};
}
