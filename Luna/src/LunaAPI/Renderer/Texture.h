#pragma once

#include "LunaAPI/Renderer/Shader.h"
#include "../../stb_image/stb_image.h"

namespace Luna {

	class Texture
	{
	public:
		unsigned int id;
		uint32_t m_ID;
		uint32_t m_Type;

		//Texture() = default;
		Texture(const char* image);
		~Texture();

		void Bind();
		void Unbind();
	};
}