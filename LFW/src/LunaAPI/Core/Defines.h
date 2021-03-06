#pragma once
#include <memory>

//INCLUDES
#include "LunaAPI/Renderer/Texture.h"
#include "LFWpch.h"

namespace LFW {

	using str = std::string; //std::string
	using i16 = uint16_t;    //uint16
	using i32 = uint32_t;    //uint32
	using i64 = uint64_t;    //uint64

	//std::vector<T>
	template <typename T>
	using Vec = std::vector<T>;

	//Add
	using AddTexture = std::shared_ptr<LFW::Texture>;

	template <typename T>
	void LoadTexture(std::shared_ptr<T>& t, const char* argument)
	{
		t = std::make_shared<T>(argument);
	}


#define DEFINE_EVENT_TYPE(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

}