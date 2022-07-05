#pragma once

namespace LFW {

	struct FramebufferSpecification
	{
		uint32_t Height, Width;
	};

	class Framebuffer
	{
	public:
		Framebuffer();//const FramebufferSpecification& fbSpec);//const char* vertexFile, const char* fragmentFile);
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
		uint32_t m_ID;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		FramebufferSpecification m_FramebufferSpecification;
	};
}