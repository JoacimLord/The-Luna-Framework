#pragma once

#include "LunaAPI/Core/Defines.h"

#include "LunaAPI/EventHandler/KeyEvents/KeyButtonBaseEvent.h"
#include "LunaAPI/EventHandler/EventDispatcher/EventDispatcher.h"
#include "LunaAPI/EventHandler/MouseEvents/MouseButtonPressed.h"

#include "LunaAPI/Renderer/Framebuffer.h"
#include "LunaAPI/Renderer/VertexArray.h"
#include "LunaAPI/Renderer/Texture.h"
#include "LunaAPI/Renderer/Renderer.h"

namespace LFW {

	class UI
	{
	public:
		UI();
		~UI();

		void OnAttach();
		void OnDetach();
		void OnEvent(Event& event);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		void BlockEvent(bool block) { blockevents = block; }

		void StartRenderFrame();
		void RenderFrame();
		void EndRenderFrame();

		void OnUIRender();

		void BindFramebuffer(float r, float g, float b, float transparent);
		void UnbindFramebuffer();
		void SetFramebufferSpec(FramebufferSpecification spec);

	public:
		std::shared_ptr<Framebuffer> m_Framebuffer;
		bool blockevents = true;
		bool m_DemoWindow = true;
		bool showDemo = false;

		bool m_DemoGuiWindow = false;
		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

	};
}