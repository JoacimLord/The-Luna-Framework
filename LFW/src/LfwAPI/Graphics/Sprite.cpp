#include "LFWpch.h"
#include "Sprite.h"


namespace LFW {

	Sprite::Sprite(glm::vec2 position, glm::vec2 size)
	{
		anchor.Translation.x = position.x;
		anchor.Translation.y = position.y;

		anchor.Scale.x = size.x;
		anchor.Scale.y = size.y;
	}

	void Sprite::SetTexture(std::string path)
	{
		if (path == "")
		{
			std::cout << "Texture path for sprite was invalid, checking sprites filepath\n";
			if(filePath != "") LoadTexture(texture, filePath.c_str(), pixelated);
			return;
		}
		else LoadTexture(texture, path.c_str(), pixelated);
	}

	void Sprite::SetPosition(float x, float y)
	{
		anchor.Translation.x = x;
		anchor.Translation.y = y;
	}

	//Gets the sprites position in 2D space (x,y)
	glm::vec2 Sprite::GetPosition()
	{
		return glm::vec2(anchor.Translation.x, anchor.Translation.y);
	}

	void Sprite::SetSize(float w, float h)
	{
		anchor.Scale.x = w;
		anchor.Scale.y = h;
	}

	glm::vec2 Sprite::GetSize()
	{
		return glm::vec2(anchor.Scale.x, anchor.Scale.y);
	}


	void Sprite::SetRotationX(float rotation)
	{
		anchor.Rotation.x += rotation;
	}

	void Sprite::SetRotationY(float rotation)
	{
		anchor.Rotation.y += rotation;
	}
	void Sprite::SetRotationZ(float rotation)
	{
		anchor.Rotation.z += rotation;
	}

	glm::mat4 Sprite::GetTransform()
	{
		return anchor.GetTransform();
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
			float topY = (currentY + spriteHeight) / (float)textureHeight;
			float rightX = (currentX + spriteWidth) / (float)textureWidth;
			float leftX = currentX / (float)textureWidth;
			float bottomY = currentY / (float)textureHeight;

			//Init mesh & data, set data and push back in vector
			{
				QuadMesh quadMesh;
				glm::vec2 textureCoordinates[4];
				textureCoordinates[0] = glm::vec2(rightX, topY);
				textureCoordinates[1] = glm::vec2(rightX, bottomY);
				textureCoordinates[2] = glm::vec2(leftX, bottomY);
				textureCoordinates[3] = glm::vec2(leftX, topY);


				QuadVertex quadVerts[] =
				{
					QuadVertex{ glm::vec3(-0.5f, -0.5f, 0.0f),   glm::vec3(1.0f, 0.0f, 0.0f),   textureCoordinates[0] },
					QuadVertex{ glm::vec3(0.5f, -0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f),   textureCoordinates[1] },
					QuadVertex{ glm::vec3(0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 0.0f, 1.0f),   textureCoordinates[2] },
					QuadVertex{ glm::vec3(-0.5f,  0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),   textureCoordinates[3] },
				};

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
		
		spritesheet.loaded = true;
	}
}