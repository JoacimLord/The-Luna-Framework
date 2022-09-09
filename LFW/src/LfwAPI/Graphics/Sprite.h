#pragma once

#include "Anchor.h"
#include "LfwAPI/Renderer/Texture.h"
#include "LfwAPI/Core/Defines.h"
#include "LfwAPI/Renderer/QuadMesh.h"

namespace LFW {

	class Sprite
	{
	public:
		//Default constructor
		Sprite() = default;

		//Sets the sprites position and size at construction
		Sprite(glm::vec2 position, glm::vec2 size);

		//Sets the sprites position, size and texture at construction
		Sprite(glm::vec2 position, glm::vec2 size, std::string filePath);

		//Adds a texture to the sprite. Load the texture with a filePath and "SetTexture()"
		AddTexture texture;

		//The filepath to the sprites texture
		std::string filePath = "";

		//Sets pixelation in texture (GL_NEAREST)
		bool pixelated = false;

		//The color of the sprite. Default value is 0
		glm::vec4 color = glm::vec4(0.0f);

		//Sets and loads a texture for the sprite. Use the filePath variable or write the filepath in the function argument
		void SetTexture(std::string path = "");

		//Sets the position of the sprite with individual values (float x, float y)
		void SetPosition(float x, float y);

		//Sets the position of the sprite with glm::vec2 (x, y)
		void SetPosition(glm::vec2 newPosition);

		//Sets the X-position of the sprite
		void SetPositionX(float x);

		//Sets the Y-position of the sprite
		void SetPositionY(float y);

		//Adds to the X-position of the sprite
		void AddPositionX(float x);

		//Adds to the Y-position of the sprite
		void AddPositionY(float y);

		//Gets the sprites position (x,y)
		glm::vec2 GetPosition();

		//Sets the size (width & height) of the sprite
		void SetSize(float w, float h);

		//Sets the width of the sprite (x axis)
		void SetWidth(float w);

		//Sets the height of the sprite (y axis)
		void SetHeight(float h);

		//Get the size of the sprite (w, h)
		glm::vec2 GetSize();

		//Get the width of the sprite
		float GetWidth();

		//Get the height of the sprite
		float GetHeight();

		//Sets the rotation of the sprite (x axis)
		void SetRotationX(float rotation);

		//Sets the rotation of the sprite (y axis)
		void SetRotationY(float rotation);

		//Sets the rotation of the sprite (z axis)
		void SetRotationZ(float rotation);

		//Adds to rotation of the sprite (x axis)
		void AddRotationX(float rotation);

		//Adds to the rotation of the sprite (y axis)
		void AddRotationY(float rotation);

		//Adds to rotation of the sprite (z axis)
		void AddRotationZ(float rotation);

		//Returns the sprites transform. Only used by the renderer to position it properly.
		glm::mat4 GetTransform();

		//Returns the sprites Anchor.
		Anchor GetAnchor();

		//Returns the sprites translation
		glm::vec3 GetTranslation();

	private:
		//The sprites placement and orientation in the world.
		//The anchor is a basic matrix with position, scale and rotation (transform).
		Anchor anchor;
	};
}
