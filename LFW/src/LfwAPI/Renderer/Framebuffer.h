#pragma once

namespace LFW {

	struct FramebufferSpecification
	{
		uint32_t height, width;
	};

	class Framebuffer
	{
	public:
		Framebuffer();
		~Framebuffer();

		void Invalidate();
		void Bind();
		void Unbind();

		void CreateFramebufferSpecification(FramebufferSpecification& fbspec);

		void ResizeFramebuffer(uint32_t width, uint32_t height);
		uint32_t& GetRendererID();
		uint32_t& GetDepthAttachment();
		uint32_t& GetColorAttachment();
		FramebufferSpecification& GetFramebufferSpecification();
	
	private:
		uint32_t m_id;
		uint32_t m_colorAttachment;
		uint32_t m_depthAttachment;
		FramebufferSpecification m_framebufferSpecification;
	};
}