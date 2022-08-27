#pragma once
#include <memory>

//INCLUDES
#include "LfwAPI/Renderer/Texture.h"
#include "LFWpch.h"

namespace LFW {

	using str = std::string;
	using i16 = uint16_t;
	using i32 = uint32_t;
	using i64 = uint64_t;

	//Adds unitialized texture
	using AddTexture = std::shared_ptr<LFW::Texture>;

	//Loads texture
	template <typename T>
	void LoadTexture(std::shared_ptr<T>& t, const char* argument, bool pixelation)
	{
		t = std::make_shared<T>(argument, pixelation);
	}


#define DEFINE_EVENT_TYPE(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

}