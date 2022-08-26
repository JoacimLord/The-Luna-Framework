#pragma once

#include "LfwAPI/Renderer/Shader.h"
#include "LfwAPI/Renderer/Framebuffer.h"
#include "LfwAPI/Renderer/VertexArray.h"
#include "LfwAPI/Renderer/Buffers.h"
#include "LfwAPI/Renderer/Texture.h"
#include "LfwAPI/Graphics/Anchor.h"
#include "LfwAPI/Graphics/Sprite.h"
#include "LfwAPI/Camera/OrthographicCamera.h"

#include "glm/glm.hpp"

namespace LFW {

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

		static OrthographicCamera GetCamera();
		static void SetCameraPosition(const glm::vec3 temppos);
		static glm::vec3 GetCameraPosition();

		//Returns the mouse position converted from world space to screen points in pixels. Origin is 0,0 (center of screen).
		glm::vec2 WorldToScreenPoint(glm::vec2 screenCoords, float screenW, float screenH);

		//Returns the mouse position converted from screen space to world point.
		//This function only returns correct values if the viewport is not initialized and uses the "original" glfw window for rendering.
		glm::vec2 ScreenToWorldPoint(float screenW, float screenH);
	};
}