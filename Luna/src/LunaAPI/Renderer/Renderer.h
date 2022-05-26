#pragma once

#include "LunaAPI/Renderer/Shader.h"
#include "LunaAPI/Renderer/Framebuffer.h"
#include "LunaAPI/Renderer/VertexArray.h"
#include "LunaAPI/Renderer/Buffers.h"
#include "LunaAPI/Renderer/Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

namespace Luna {

	struct Statistics
	{
		uint32_t DrawCalls = 0;
	};

	//Change to a namespace and remove class?
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

	public:
		static void Init();
		static void Clear();
		static void ClearColor(float r, float g, float b, float transparent);
		static void Draw(std::shared_ptr<Texture>& texture, glm::mat4 entityTransform);
		static void Draw(Texture texture, glm::mat4 entityTransform);
		static void DrawElements(std::shared_ptr<VertexArray>& vertexArray, uint32_t size);
		static void OpenGLEnables();

		//NEW!! - 220526
		static void OnWindowResize(float width, float height);



		static Statistics GetDrawCalls();
		static void ClearFrame(float r, float g, float b, float transparent);
	};

	//Transform
	struct Anchor
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		//Constructor!
		Anchor() = default;
		Anchor(const Anchor&) = default;
		Anchor(glm::vec3& translation)
			: Translation(translation)
		{

		}

		//Scale in constructor?
		Anchor(glm::vec3& translation, glm::vec3& scale)
			: Translation(translation), Scale(scale)
		{

		}

		glm::mat4 GetTransform()
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
			//* glm::rotate(glm::mat4(1.0f), { 0.0f, 0.0f, 1.0f })); //TRANSLATES THE TEXTURE
		}
	};
}