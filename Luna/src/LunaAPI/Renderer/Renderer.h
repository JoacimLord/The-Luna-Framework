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

//test
#include "LunaAPI/Core/Input.h"

namespace Luna {

	//OrthoCam - NEW
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
			//Do nothing
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


	struct Statistics
	{
		uint32_t DrawCalls = 0;
	};

	//Push into a namespace and remove class, is it really needed?
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

	public:
		static void Init();
		static void Clear();
		static void ClearColor(float r, float g, float b, float transparent);

		static void Draw(std::shared_ptr<Texture>& texture, const glm::mat4& entityTransform);

		static void DrawElements(std::shared_ptr<VertexArray>& vertexArray, uint32_t size);
		static void OpenGLEnables();

		//Added 220526
		static void OnWindowResize(float width, float height);

		static void Draw(glm::vec4 clr, const glm::mat4& entityTransform); //by ref(&)?

		static void BindColorFromValues(glm::vec4 clrIn, static float clrOut[4]); //by ref(&)?

		static Statistics GetDrawCalls();
		static void ClearFrame(float r, float g, float b, float transparent);		

		static OrthoCam GetCamera();
		static void SetCameraPosition(const glm::vec3 temppos);
		static glm::vec3 GetCameraPosition();
		
	private:
		//Move to vec4 aspectRatio_16x9?
		float l = -1.6f;
		float r = 1.6f;
		float b = -0.9f;
		float t = 0.9f;
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