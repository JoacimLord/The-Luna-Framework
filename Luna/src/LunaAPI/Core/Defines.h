#pragma once
#include <memory>

/*
	Thanks The Cherno and his guides for this and the event system! Much appreciated :)
*/

namespace Luna {

#define BIT(x) (1 << x)
#define DEFINE_EVENT_TYPE(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
}