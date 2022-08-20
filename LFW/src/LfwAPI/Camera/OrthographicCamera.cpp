#include "LFWpch.h"
#include "OrthographicCamera.h"

namespace LFW {

	OrthographicCamera::OrthographicCamera(float l, float r, float b, float t)
		: projMatrix(glm::ortho(l, r, b, t, -1.0f, 1.0f)) //TODO: Remove this
	{
		aspectRatio = 16.0f / 9.0f;
		RecalcMatrix();
		SetProjection(l, r, b, t);
	}

	const glm::vec3& OrthographicCamera::GetPosition() const { return pos; }

	void OrthographicCamera::RecalcMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) *
			glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1));

		viewMatrix = glm::inverse(transform);
		viewProjMatrix = projMatrix * viewMatrix;
	}
	void OrthographicCamera::SetPosition(const glm::vec3& temppos) { pos = temppos; RecalcMatrix(); }

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		projMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		viewProjMatrix = projMatrix * viewMatrix;
	}
	void OrthographicCamera::OnResize(float width, float height)
	{
		aspectRatio = width / height;
		bounds = { -aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel };
		SetProjection(bounds.Left, bounds.Right, bounds.Bottom, bounds.Top);
	}
}