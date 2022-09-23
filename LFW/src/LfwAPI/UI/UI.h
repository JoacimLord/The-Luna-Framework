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

	//This class is used by Application to initialize and render GUI
	class UI
	{
	public:
		UI();
		~UI();

		void OnAttach();
		void OnDetach();

		void StartRenderFrame();
		void RenderFrame();
		void EndRenderFrame();

		void OnUIRender();

		void BindFramebuffer(float r, float g, float b, float transparent);
		void UnbindFramebuffer();
		void SetFramebufferSpec(FramebufferSpecification spec);

	public:
		bool showDemo = false;
		glm::vec2 viewportSize = { 0.0f, 0.0f };
		glm::vec2 mousePosition = { 0.0f, 0.0f };
		glm::vec2 m_ViewportBounds[2];

	private:
		std::shared_ptr<Framebuffer> m_framebuffer;

		bool m_blockevents = true;
		bool m_demoWindow = true;

		bool m_demoGuiWindow = false;
	};
}