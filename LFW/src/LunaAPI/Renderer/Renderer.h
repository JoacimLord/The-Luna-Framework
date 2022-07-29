#pragma once

#include "LunaAPI/Renderer/Shader.h"
#include "LunaAPI/Renderer/Framebuffer.h"
#include "LunaAPI/Renderer/VertexArray.h"
#include "LunaAPI/Renderer/Buffers.h"
#include "LunaAPI/Renderer/Texture.h"
#include "LunaAPI/Graphics/Anchor.h"
#include "LunaAPI/Graphics/Sprite.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>


namespace LFW {

	//OrthoCam - WIP
	class OrthoCam
	{
	public:
		glm::mat4 projMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjMatrix;

		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		float rotation = 0.0f;

		OrthoCam(float l, float r, float b, float t)
			: projMatrix(glm::ortho(l, r, b, t, -1.0f, 1.0f))
		{
			RecalcMatrix();
		}

		const glm::vec3& GetPos() const { return pos; }

		void RecalcMatrix()
		{
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
				glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1));

			viewMatrix = glm::inverse(transform);
			viewProjMatrix = projMatrix * viewMatrix;
		}
		void SetPos(const glm::vec3& temppos) { pos = temppos; RecalcMatrix(); }
	};

	class Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;

	public:
		static void Init();
		static void Clear();
		static void ClearColor(float r, float g, float b, float transparent);

		static void Draw(Sprite sprite);

		static void DrawElements(std::shared_ptr<VertexArray>& vertexArray, uint32_t size);
		static void OpenGLEnables();

		static void OnWindowResize(float width, float height);

		static void ClearFrame(float r, float g, float b, float transparent);		

		static OrthoCam GetCamera();
		static void SetCameraPosition(const glm::vec3 temppos);
		static glm::vec3 GetCameraPosition();
	};
}