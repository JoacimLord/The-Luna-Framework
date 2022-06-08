#pragma once

#include "LunaAPI/Core/Defines.h"
#include "LunaAPI/EventHandler/KeyEvents/KeyButtonBaseEvent.h"

#include "LunaAPI/Renderer/Framebuffer.h"
#include "LunaAPI/Renderer/VertexArray.h"
#include "LunaAPI/Renderer/Texture.h"
#include "LunaAPI/Renderer/Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace Luna {

	class UI
	{
	public:
		std::shared_ptr<Framebuffer> m_Framebuffer;

		bool m_DemoWindow = true;
		bool showDemo = false;

		std::string m_LayerName;

		bool m_DemoGuiWindow = false;
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

	public:
		UI();
		~UI();

		void OnAttach();
		void OnDetach();
		void OnEvent(Event& event);

		void StartRenderFrame();
		void RenderFrame();
		void EndRenderFrame();

	public:
		void OnUIRender();

		void BindFramebuffer(float r, float g, float b, float transparent);
		void UnbindFramebuffer();
		void SetFramebufferSpec(FramebufferSpecification spec);
	};
}