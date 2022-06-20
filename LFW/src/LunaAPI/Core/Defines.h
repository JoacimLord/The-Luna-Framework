#pragma once
#include <memory>

namespace Luna {

#define DEFINE_EVENT_TYPE(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
}