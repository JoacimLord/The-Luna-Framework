#pragma once
#include "Sprite.h"
#include "LfwAPI/Renderer/QuadMesh.h"


namespace LFW {

	//Batch for 'Instanced' rendering - WIP!
	//The Instanced rendering is currently set up to move the sprite x amount of pixels to the right after each instance.
	//This will be fixed and is only for demo purposes.
	//Don't use this functionality before changing it yourself.
	struct Batch 
	{
		//TODO: Can be a single Sprite instance, no need for a vector at this stage.
		std::vector<Sprite> sprites;

		//TODO: Remove this?
		std::vector<QuadMesh> quads;
		//std::vector<VertexArray> VAOs;
	};

	//Hold texture coordiantes from a single spritesheet to iterate over them by the same sprite.
	struct TextureCoords
	{
		glm::vec2 coords[4];
	};

	//Contains the spritesheet data.
	//This needs to be set and pushed back before rendering.
	//Multiple variables in Spritesheet is not supposed to be changed, don't use these.
	//I will 'abstract' them away eventually!
	struct Spritesheet
	{
		//Compare the for-loop in rendering with sprites since the amount of quads in the spritesheet doesn't equal the amount of sprites to draw.
		//The vector of sprites is if you intend to have multiple sprites that use the same spritesheet.
		//If there's only one sprite for a spritesheet (for example if there is a single animation), then only use a single sprite slot in the vector.
		std::vector<Sprite> sprites;

		//DON'T change this manually. Used by the SpriteSheetManager.
		AddTexture spritesheet;

		//DON'T change this manually. Used by the SpriteSheetManager.
		const char* filePath = "";

		//DON'T change this manually. Used by the SpriteSheetManager to determine if the spritesheet has been loaded properly.
		bool loaded = false;

		//Texture coordinates extracted from a single spritesheet.
		std::vector<TextureCoords> textureCoords;

		//Add sprites.
		void AddSprite(Sprite& sprite);

		//Returns sprite based on index.
		Sprite& GetSprite(int index);

	};

	//Used to manage single spritesheets.
	//Remember that LoadSpritesheet() and CreateSpritesheet() has to be called for each individual spritesheet.
	namespace SpritesheetManager
	{
		//Loads the spritesheet. 
		//Takes in the spritesheet, filepath and if the sprites needs pixelation (for pixel art)
		void LoadSpritesheet(Spritesheet& spritesheet, const char* filePath, bool pixelation);

		//Creates the spritesheet.
		//Set spritesheet width & height, sprite width & height,
		//number of sprites and if there is any spacing between the sprites(in pixels)
		void CreateSpritesheet(Spritesheet& spritesheet, int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int numberofSprites, int spacing);
	}
}
