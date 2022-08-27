#pragma once
#include "Sprite.h"
#include "LfwAPI/Renderer/QuadMesh.h"

namespace LFW {

	struct Spritesheet
	{
		//This needs to be set and pushed back before rendering.
		//Compare the for-loop in rendering with sprites since the amount of quads in the spritesheet doesn't equal the amount of sprites to draw.
		std::vector<Sprite> sprites;
		std::vector< QuadMesh> quads;
		AddTexture spritesheet;
		const char* filePath = "";
		bool loaded = false;

		//Add sprites
		void AddSprite(Sprite& sprite);
		Sprite& GetSprite(int index);
	};


	namespace SpritesheetManager
	{
		//Sets the texture
		void LoadSpritesheet(Spritesheet& spritesheet, const char* filePath, bool pixelation);

		//Creates the spritesheet
		void CreateSpritesheet(Spritesheet& spritesheet, int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int numberofSprites, int spacing);
	}
}
