#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

namespace LFW {

	//TODO: Rename to Transform?
	struct Anchor
	{
		//Position in world space
		glm::vec3 translation = { 0.0f, 0.0f, 0.0f };

		//Rotation in world space
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };

		//Scale in world space
		glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

		Anchor() = default;
		Anchor(const Anchor&) = default;
		Anchor(glm::vec3& translation);
		Anchor(glm::vec3& translation, glm::vec3& scale);

		//Returns transform components
		glm::mat4 GetTransform();
	};
}