#pragma once

#include "LfwAPI/Renderer/Shader.h"
#include "LfwAPI/Renderer/Framebuffer.h"
#include "LfwAPI/Renderer/VertexArray.h"
#include "LfwAPI/Renderer/Buffers.h"
#include "LfwAPI/Renderer/Texture.h"
#include "LfwAPI/Graphics/Anchor.h"
#include "LfwAPI/Graphics/Sprite.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>


namespace LFW {


	struct OrthoCamBounds
	{
		float Left, Right, Bottom, Top;
		float GetWidth() { return Right - Left; }
		float GetHeigt() { return Top - Bottom; }
	};

	//OrthoCam - WIP
	class OrthoCam
	{
	public:
		OrthoCamBounds bounds;
		glm::mat4 projMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjMatrix;

		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		float rotation = 0.0f;
		float aspectRatio;
		float zoomLevel = 1.0f;

		OrthoCam(float l, float r, float b, float t)
			: projMatrix(glm::ortho(l, r, b, t, -1.0f, 1.0f))
		{
			aspectRatio = 16.0f / 9.0f;
			RecalcMatrix();
			SetProjection(l, r, b, t);
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

		void SetProjection(float left, float right, float bottom, float top)
		{
			projMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
			viewProjMatrix = projMatrix * viewMatrix;
		}
		void OnResize(float width, float height)
		{
			aspectRatio = width / height;
			bounds = {-aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel};
			SetProjection(bounds.Left, bounds.Right, bounds.Bottom, bounds.Top);
		}
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

		static void Draw(Sprite& sprite);

		static void DrawElements(std::shared_ptr<VertexArray>& vertexArray, uint32_t size);
		static void OpenGLEnables();

		static void OnWindowResize(float width, float height);


		static OrthoCam GetCamera();
		static void SetCameraPosition(const glm::vec3 temppos);
		static glm::vec3 GetCameraPosition();
	};
}