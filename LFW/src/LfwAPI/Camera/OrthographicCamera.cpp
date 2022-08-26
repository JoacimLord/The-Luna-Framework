#include "LFWpch.h"
#include "OrthographicCamera.h"
#include "LfwAPI/Core/Input.h"

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

	void OrthographicCamera::SetPosition(const glm::vec3& temppos) 
	{
		pos = temppos; 
		xOffset = pos.x;
		yOffset = pos.y;
		std::cout << "X: " << xOffset << "\n";
		std::cout << "Y: " << yOffset << "\n";
		RecalcMatrix(); 
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		projMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		viewProjMatrix = projMatrix * viewMatrix;
	}

	glm::vec2 OrthographicCamera::WorldToScreenPoint(glm::vec2 screenCoords, float screenW, float screenH)
	{
		screenCoords -= glm::vec2((float)screenW / 2, (float)screenH / 2);
		screenCoords /= zoomLevel;
		screenCoords.x += pos.x;
		screenCoords.y += pos.y;

		// Flips the y-axis
		glm::vec2 temp = glm::vec2(screenCoords.x, -screenCoords.y);
		return temp;
	}

	glm::vec2 OrthographicCamera::ScreenToWorldPoint(float screenW, float screenH)
	{
		// X
		float currentX = Input::GetMousePositionX();
		currentX = (currentX / screenW) * 2.0f - 1.0f;
		glm::vec4 tempX = glm::vec4(currentX, 0.0f, 0.0f, 1.0f);

		glm::mat4 inversedProjectionX = glm::inverse(projMatrix);
		glm::mat4 inversedViewX = glm::inverse(viewMatrix);

		glm::vec4 viewProjMatrixX = tempX * inversedProjectionX * inversedViewX;
		currentX = viewProjMatrixX.x;

		// Y
		float currentY = Input::GetMousePositionY();
		currentY = (currentY / screenH) * 2.0f - 1.0f;
		glm::vec4 tempY = glm::vec4(0.0f, currentY, 0.0f, 1.0f);

		glm::mat4 inversedProjectionY = glm::inverse(projMatrix);
		glm::mat4 inversedViewY = glm::inverse(viewMatrix);

		glm::vec4 viewProjMatrixY = tempY * inversedProjectionY * inversedViewY;
		currentY = -viewProjMatrixY.y;

		glm::vec2 mousePositionInWorld = glm::vec2(currentX, currentY);


		mousePositionInWorld.y += yOffset;
		mousePositionInWorld.x += xOffset;

		return mousePositionInWorld;
	}


	void OrthographicCamera::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowResizeEvent>(DEFINE_EVENT_TYPE(OrthographicCamera::OnResizedEvent));
	}
	void OrthographicCamera::OnResize(float width, float height)
	{
		aspectRatio = width / height;
		bounds = { -aspectRatio * zoomLevel, aspectRatio * zoomLevel, -zoomLevel, zoomLevel };
		SetProjection(bounds.Left, bounds.Right, bounds.Bottom, bounds.Top);

		//Debug
		//std::cout << "Width: " << width << ", height: " << height << ", ar: " << aspectRatio << "\n";
	}


	bool OrthographicCamera::OnResizedEvent(WindowResizeEvent& e)
	{
		std::cout << "Resizing from camera!" << "\n";
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}
}