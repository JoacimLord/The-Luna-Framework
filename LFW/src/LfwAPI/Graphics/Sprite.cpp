#include "LFWpch.h"
#include "Sprite.h"


namespace LFW {

	Sprite::Sprite(glm::vec2 position, glm::vec2 size)
	{
		anchor.translation.x = position.x;
		anchor.translation.y = position.y;

		anchor.scale.x = size.x;
		anchor.scale.y = size.y;
	}

	Sprite::Sprite(glm::vec2 position, glm::vec2 size, std::string filePath)
	{
		anchor.translation.x = position.x;
		anchor.translation.y = position.y;

		anchor.scale.x = size.x;
		anchor.scale.y = size.y;

		SetTexture(filePath);
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
		anchor.translation.x = x;
		anchor.translation.y = y;
	}

	void Sprite::SetPosition(glm::vec2 newPosition)
	{
		anchor.translation.x = newPosition.x;
		anchor.translation.y = newPosition.y;
	}

	void Sprite::SetPositionX(float x)
	{
		anchor.translation.x = x;
	}

	void Sprite::SetPositionY(float y)
	{
		anchor.translation.y = y;
	}

	void Sprite::AddPositionX(float x)
	{
		anchor.translation.x += x;
	}

	void Sprite::AddPositionY(float y)
	{
		anchor.translation.y += y;
	}

	glm::vec2 Sprite::GetPosition()
	{
		return glm::vec2(anchor.translation.x, anchor.translation.y);
	}

	void Sprite::SetSize(float w, float h)
	{
		anchor.scale.x = w;
		anchor.scale.y = h;
	}

	void Sprite::SetWidth(float w)
	{
		anchor.scale.x = w;
	}

	void Sprite::SetHeight(float h)
	{
		anchor.scale.y = h;
	}

	glm::vec2 Sprite::GetSize()
	{
		return glm::vec2(anchor.scale.x, anchor.scale.y);
	}

	float Sprite::GetWidth()
	{
		return anchor.scale.x;
	}

	float Sprite::GetHeight()
	{
		return anchor.scale.y;
	}

	void Sprite::SetRotationX(float rotation)
	{
		anchor.rotation.x = rotation;
	}

	void Sprite::SetRotationY(float rotation)
	{
		anchor.rotation.y = rotation;
	}
	void Sprite::SetRotationZ(float rotation)
	{
		anchor.rotation.z = rotation;
	}
	void Sprite::AddRotationX(float rotation)
	{
		anchor.rotation.x += rotation;
	}

	void Sprite::AddRotationY(float rotation)
	{
		anchor.rotation.y += rotation;
	}

	void Sprite::AddRotationZ(float rotation)
	{
		anchor.rotation.z += rotation;
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
		return anchor.translation;
	}
}