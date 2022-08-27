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

	//Loads in the texture
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
				QuadMesh quadMesh;
				glm::vec2 textureCoordinates[4];
				textureCoordinates[0] = glm::vec2(right, top);
				textureCoordinates[1] = glm::vec2(right, bottom);
				textureCoordinates[2] = glm::vec2(left,  bottom);
				textureCoordinates[3] = glm::vec2(left,  top);


				QuadVertex quadVerts[] =
				{
					QuadVertex{ glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec3(1.0f, 0.0f, 0.0f),   textureCoordinates[0] },
					QuadVertex{ glm::vec3(0.5f, -0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f),   textureCoordinates[1] },
					QuadVertex{ glm::vec3(0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 0.0f, 1.0f),   textureCoordinates[2] },
					QuadVertex{ glm::vec3(-0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   textureCoordinates[3] },
				};

				//Set the verticies of the quads and add to vector
				std::vector <QuadVertex> verts(quadVerts, quadVerts + sizeof(quadVerts) / sizeof(QuadVertex));
				quadMesh.verticies = verts;
				spritesheet.quads.push_back(quadMesh);
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