#include "Lunapch.h"
#include "Framebuffer.h"
#include <glad/glad.h>

namespace Luna {

    Framebuffer::Framebuffer()//const FramebufferSpecification& fbSpec)//const char* vertexFile, const char* fragmentFile)
     //   :m_FramebufferSpecification(fbSpec)
    {
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &m_ID);
    }

    void Framebuffer::Invalidate()
    {
        glCreateFramebuffers(1, &m_ID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
        glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorAttachment);

        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_FramebufferSpecification.Width, m_FramebufferSpecification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Prevents edge bleeding

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "Framebuffer loaded!\n";
        }
       glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment); //Görs redan??
 
        //glfwGetFramebufferSize(window, &displayWidth, &displayHeight);
        glViewport(0, 0, m_FramebufferSpecification.Width, m_FramebufferSpecification.Height);

    }

    void Framebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::CreateFramebufferSpecification(FramebufferSpecification& fbspec)
    {
        m_FramebufferSpecification.Height = fbspec.Height;
        m_FramebufferSpecification.Width = fbspec.Width;
    }

    uint32_t& Framebuffer::GetRendererID() { return m_ID; }
    uint32_t& Framebuffer::GetDepthAttachment() { return m_DepthAttachment; }
    uint32_t& Framebuffer::GetColorAttachment() { return m_ColorAttachment; }
    FramebufferSpecification& Framebuffer::GetFramebufferSpecification() { return m_FramebufferSpecification; }
}