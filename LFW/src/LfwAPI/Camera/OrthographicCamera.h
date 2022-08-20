#pragma once

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

		OrthographicCamera(float l, float r, float b, float t);
		const glm::vec3& GetPosition() const;
		void RecalcMatrix();
		void SetPosition(const glm::vec3& temppos);

		void SetProjection(float left, float right, float bottom, float top);
		void OnResize(float width, float height);
	};

}