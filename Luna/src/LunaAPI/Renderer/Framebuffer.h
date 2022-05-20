#pragma once

namespace Luna {

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

		uint32_t& GetRendererID();// { return m_ID; }
		uint32_t& GetDepthAttachment();// { return m_DepthAttachment; }
		uint32_t& GetColorAttachment();// { return m_ColorAttachment; }
		FramebufferSpecification& GetFramebufferSpecification();// { return m_FramebufferSpecification; }
	
	private:
		uint32_t m_ID;
		uint32_t m_ColorAttachment;
		uint32_t m_DepthAttachment;
		FramebufferSpecification m_FramebufferSpecification;
	};
}