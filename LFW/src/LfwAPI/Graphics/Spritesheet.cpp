#include "LFWpch.h"
#include "Spritesheet.h"

namespace LFW {


	void Spritesheet::AddSprite(Sprite& sprite)
	{
		sprites.push_back(sprite);
	}

	Sprite& Spritesheet::GetSprite(int index)
	{
		return sprites[index];
	}

	void SpritesheetManager::LoadSpritesheet(Spritesheet& spritesheet, const char* filePath, bool pixelation)
	{
		LoadTexture(spritesheet.spritesheet, filePath, pixelation);
	}

	//Sets texture coordinates of each 2d quad. This does not load the texture, just the quads and their positions on the sheet
	void SpritesheetManager::CreateSpritesheet(Spritesheet& spritesheet, int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int numberofSprites, int spacing)
	{
		int currentX = 0;
		int currentY = textureHeight - spriteHeight;

		for (int i = 0; i < numberofSprites; i++)
		{
			float top = (currentY + spriteHeight) / (float)textureHeight;
			float right = (currentX + spriteWidth) / (float)textureWidth;
			float left = currentX / (float)textureWidth;
			float bottom = currentY / (float)textureHeight;

			//Init mesh & data, set data and push back in vector
			{
				//Get the texture coordiantes
				glm::vec2 textureCoordinates[4];
				textureCoordinates[0] = glm::vec2(left, bottom);
				textureCoordinates[1] = glm::vec2(right, bottom);
				textureCoordinates[2] = glm::vec2(right, top);
				textureCoordinates[3] = glm::vec2(left, top);

				//Add the texture coordinates in vector to save for later usage
				TextureCoords coords;
				coords.coords[0] = textureCoordinates[0];
				coords.coords[1] = textureCoordinates[1];
				coords.coords[2] = textureCoordinates[2];
				coords.coords[3] = textureCoordinates[3];

				spritesheet.textureCoords.push_back(coords);
			}

			//Skip to next sprite in the spritesheet
			currentX += spriteWidth + spacing;
			if (currentX >= textureWidth)
			{
				currentX = 0;
				currentY -= spriteHeight + spacing;
			}
		}

		//Set the spritesheet to be loaded and done
		spritesheet.loaded = true;
	}
}