#pragma once

#include "LfwAPI/Renderer/Shader.h"
#include "../../stb_image/stb_image.h"

namespace LFW {

	class Texture
	{
	public:
		unsigned int id;

		//Texture() = default;
		Texture(const char* image, bool pixelation);
		~Texture();

		void Bind();
		void Unbind();
	};
}