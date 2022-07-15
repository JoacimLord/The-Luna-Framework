#pragma once

//#include "LFWpch.h"
#include "Anchor.h"
#include "LunaAPI/Renderer/Texture.h"
#include "LunaAPI/Core/Defines.h"

namespace LFW {

	struct Sprite
	{
		Anchor anchor; // This a matrix with position, scale and rotation.
		AddTexture texture;
		std::string filePath;

		//Default is 0
		glm::vec4 color = glm::vec4(0.0f);

		void SetTexture(std::string path);
		void SetPosition(float x, float y);
		void SetSize(float w, float h);
		void SetRotationX(float rotation);
		void SetRotationY(float rotation);
		void SetRotationZ(float rotation);
	};
}
