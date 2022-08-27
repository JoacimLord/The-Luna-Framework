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

	Anchor Sprite::GetAnchor()
	{
		return anchor;
	}

	glm::vec3 Sprite::GetTranslation()
	{
		return anchor.Translation;
	}

}