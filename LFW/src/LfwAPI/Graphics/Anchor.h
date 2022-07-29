#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

namespace LFW {

	//TODO: Rename to Transform?
	struct Anchor
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		Anchor() = default;
		Anchor(const Anchor&) = default;
		Anchor(glm::vec3& translation);
		Anchor(glm::vec3& translation, glm::vec3& scale);

		glm::mat4 GetTransform();
	};
}