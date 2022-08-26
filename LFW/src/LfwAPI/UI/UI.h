#pragma once

#include "LfwAPI/Core/Defines.h"

#include "LfwAPI/EventHandler/KeyEvents/KeyButtonBaseEvent.h"
#include "LfwAPI/EventHandler/EventDispatcher/EventDispatcher.h"
#include "LfwAPI/EventHandler/MouseEvents/MouseButtonPressed.h"

#include "LfwAPI/Renderer/Framebuffer.h"
#include "LfwAPI/Renderer/VertexArray.h"
#include "LfwAPI/Renderer/Texture.h"
#include "LfwAPI/Renderer/Renderer.h"

namespace LFW {

	class UI
	{
	public:
		UI();
		~UI();

		void OnAttach();
		void OnDetach();
		void OnEvent(Event& event);
		void BlockEvent(bool block) { blockevents = block; }

		void StartRenderFrame();
		void RenderFrame();
		void EndRenderFrame();

		void OnUIRender();

		void BindFramebuffer(float r, float g, float b, float transparent);
		void UnbindFramebuffer();
		void SetFramebufferSpec(FramebufferSpecification spec);

	public:
		bool showDemo = false;
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

	private:
		std::shared_ptr<Framebuffer> m_Framebuffer;

		bool blockevents = true;
		bool m_DemoWindow = true;

		bool m_DemoGuiWindow = false;
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;
	};
}