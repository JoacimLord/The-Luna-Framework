#pragma once


#include "LunaAPI/Core/Defines.h"
#include "LunaAPI/Event/ApplicationEvent.h"
#include "LunaAPI/Event/KeyEvent.h"
#include "LunaAPI/Event/MouseEvent.h"

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
		const char* THEME_DARK = "dark";
		const char* THEME_LIGHT = "light";

		const std::string THEME_DARK2 = "dark";
		const std::string THEME_LIGHT2 = "light";

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
		void SetThemeColors(const std::string& theme);

	public:
		void OnUIRender();

		void BindFramebuffer(float r, float g, float b, float transparent);
		void UnbindFramebuffer();
		void SetFramebufferSpec(FramebufferSpecification spec);
	};
}