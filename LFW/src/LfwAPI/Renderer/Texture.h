#pragma once

#include "LfwAPI/Renderer/Shader.h"
#include "../../stb_image/stb_image.h"

namespace LFW {

	class Texture
	{
	public:
		unsigned int id;

		//Takes in a filepath and if the texture should be pixelated or not
		Texture(const char* image, bool pixelation);
		~Texture();

		void Bind();
		void Unbind();
	};
}