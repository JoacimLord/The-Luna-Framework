#include "LFWpch.h"
#include "Anchor.h"

namespace LFW {

	Anchor::Anchor(glm::vec3& translation)
		: translation(translation)
	{
	}
	Anchor::Anchor(glm::vec3& translation, glm::vec3& scale)
		: translation(translation), scale(scale)
	{
	}

	glm::mat4 Anchor::GetTransform()
	{
		glm::mat4 tempRotation = glm::toMat4(glm::quat(rotation));

		return glm::translate(glm::mat4(1.0f), translation)
			* tempRotation
			* glm::scale(glm::mat4(1.0f), scale);
		//* glm::rotate(glm::mat4(1.0f), { 0.0f, 0.0f, 1.0f })); //TRANSLATES THE TEXTURE
	}
}