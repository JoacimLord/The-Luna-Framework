#include "LFWpch.h"
#include "Sprite.h"


namespace LFW {


	void Sprite::SetTexture(std::string path)
	{
		//debug msg here, if path is empty
		if (path == "") return;

		if(filePath != "") LoadTexture(texture, filePath.c_str());
		else LoadTexture(texture, path.c_str());
	}

	void Sprite::SetPosition(float x, float y)
	{
		anchor.Translation.x = x;
		anchor.Translation.y = y;
	}

	void Sprite::SetSize(float w, float h)
	{
		anchor.Scale.x = w;
		anchor.Scale.y = h;
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
}