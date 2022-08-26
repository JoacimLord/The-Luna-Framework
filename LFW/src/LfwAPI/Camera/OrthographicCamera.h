#pragma once


#include "LfwAPI/EventHandler/WindowEvents/WindowResize.h"
#include "LfwAPI/EventHandler/EventDispatcher/EventDispatcher.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace LFW {

	class OrthographicCamera
	{
	private:
		struct OrthographicCameraBounds
		{
			float Left, Right, Bottom, Top;
			float GetWidth() { return Right - Left; }
			float GetHeigt() { return Top - Bottom; }
		};

	public:
		OrthographicCameraBounds bounds;
		glm::mat4 projMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjMatrix;

		glm::vec3 pos = { 0.0f, 0.0f, 0.0f };
		float rotation = 0.0f;
		float aspectRatio;
		float zoomLevel = 1.0f;

		float xOffset = 0;
		float yOffset = 0;

		OrthographicCamera(float l, float r, float b, float t);
		const glm::vec3& GetPosition() const;
		void RecalcMatrix();
		void SetPosition(const glm::vec3& temppos);

		void SetProjection(float left, float right, float bottom, float top);

		//Returns the mouse position converted from world space to screen points in pixels. Origin is 0,0 (center of screen).
		glm::vec2 WorldToScreenPoint(glm::vec2 screenCoords, float screenW, float screenH);

		//Returns the mouse position converted from screen space to world point.
		//This function only returns correct values if the viewport is not initialized and uses the "original" glfw window for rendering.
		glm::vec2 ScreenToWorldPoint(float screenW, float screenH);

		void OnEvent(Event& event);
		void OnResize(float width, float height);

		bool OnResizedEvent(WindowResizeEvent& e);
	};
}