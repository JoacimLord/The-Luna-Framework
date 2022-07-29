#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace LFW {

	namespace Colors {

		//TODO: Set these to const, conflicts with the clear functions.
		static glm::vec4 Pink  = { 1.0f, 0.0f, 1.0f, 1.0f };
		static glm::vec4 Red   = { 1.0f, 0.0f, 0.0f, 1.0f };
		static glm::vec4 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
		static glm::vec4 Blue  = { 0.0f, 0.0f, 1.0f, 1.0f };
		static glm::vec4 Teal  = { 0.0f, 0.5f, 0.5f, 1.0f };
		static glm::vec4 Grey  = { 0.5f, 0.5f, 0.5f, 1.0f };
		static glm::vec4 Orange = { 1.0f, .5f, 0.0f, 1.0f };
		static glm::vec4 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
		static glm::vec4 White = { 1.0f, 1.0f, 1.0f, 1.0f };
		static glm::vec4 Lightgreen = { .5f, 1.0f, 0.0f, 1.0f };

		//LFW::Vec4 clr = { 1.0f, 0.0f, 1.0f, 1.0f };
	}
}