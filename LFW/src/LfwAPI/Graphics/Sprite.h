#pragma once

//#include "LFWpch.h"
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

		//Adds a texture to the sprite. Load the texture with a filePath and "SetTexture()"
		AddTexture texture;

		//The filepath to the sprites texture
		std::string filePath = "";

		//Sets pixelation in texture (GL_NEAREST)
		bool pixelated = false;

		//The color of the sprite. 
		//Default value is 0.
		glm::vec4 color = glm::vec4(0.0f);

		//Sets and loads a texture for the sprite. Use the filePath variable or write the filepath in the function argument
		void SetTexture(std::string path = "");

		//Sets the position of the sprite in 2D space (x, y)
		void SetPosition(float x, float y);

		//Gets the sprites position in 2D space (x,y)
		glm::vec2 GetPosition();

		//Sets the size of the sprite in 2D space (x, y)
		void SetSize(float w, float h);

		//Get the size of the sprite in 2D space (x, y)
		glm::vec2 GetSize();

		//Sets the rotation of the sprite in 2D space (x axis)
		void SetRotationX(float rotation);

		//Sets the rotation of the sprite in 2D space (y axis)
		void SetRotationY(float rotation);

		//Sets the rotation of the sprite in 2D space (z axis)
		void SetRotationZ(float rotation);

		//Returns the sprites transform. Only used by the renderer to position it properly.
		glm::mat4 GetTransform();

	private:
		//The sprites placement and orientation in the world.
		//The anchor is a basic matrix with position, scale and rotation (transform).
		Anchor anchor;
	};


	//WIP - Don't use! Not tested.
	struct Spritesheet
	{
		//This needs to be set and pushed back before rendering.
		//Compare the for-loop in rendering with sprites since the amount of quads in the spritesheet doesn't equal the amount of sprites to draw.
		std::vector<Sprite> sprites;
		std::vector< QuadMesh> quads;
		AddTexture spritesheet;
		const char* filePath = "";
		bool loaded = false;
	};


	//WIP - Don't use! Not tested.
	struct SpritesheetManager
	{
		//Sets the texture
		void LoadSpritesheet(Spritesheet& spritesheet, const char* filePath, bool pixelation);

		//Creates the spritesheet
		void CreateSpritesheet(Spritesheet& spritesheet, int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int numberofSprites, int spacing);
	};
}
