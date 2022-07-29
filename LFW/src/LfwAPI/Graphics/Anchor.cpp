#include "LFWpch.h"
#include "Anchor.h"

namespace LFW {

	Anchor::Anchor(glm::vec3& translation)
		: Translation(translation)
	{
	}
	Anchor::Anchor(glm::vec3& translation, glm::vec3& scale)
		: Translation(translation), Scale(scale)
	{
	}

	glm::mat4 Anchor::GetTransform()
	{
		glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

		return glm::translate(glm::mat4(1.0f), Translation)
			* rotation
			* glm::scale(glm::mat4(1.0f), Scale);
		//* glm::rotate(glm::mat4(1.0f), { 0.0f, 0.0f, 1.0f })); //TRANSLATES THE TEXTURE
	}
}