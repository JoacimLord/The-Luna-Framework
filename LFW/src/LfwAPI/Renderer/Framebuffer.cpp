#include "LFWpch.h"
#include "Framebuffer.h"
#include <glad/glad.h>

namespace LFW {

    Framebuffer::Framebuffer()
    {
    }

    Framebuffer::~Framebuffer()
    {
        glDeleteFramebuffers(1, &m_id);
    }

    void Framebuffer::Invalidate()
    {
        if (m_id)
        {
            std::cout << "Resizing framebuffer\n";
            glDeleteFramebuffers(1, &m_id);
            glDeleteTextures(1, &m_colorAttachment);
            glDeleteTextures(1, &m_depthAttachment);

            m_colorAttachment = 0;
            m_depthAttachment = 0;
        }

        glCreateFramebuffers(1, &m_id);
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);

        glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_framebufferSpecification.width, m_framebufferSpecification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Prevents edge bleeding
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_colorAttachment, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "Framebuffer loaded!\n";
        }

       glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_id);
        glBindTexture(GL_TEXTURE_2D, m_colorAttachment); //TODO: Remove?
 
        glViewport(0, 0, m_framebufferSpecification.width, m_framebufferSpecification.height);

    }

    void Framebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Framebuffer::CreateFramebufferSpecification(FramebufferSpecification& fbspec)
    {
        m_framebufferSpecification.height = fbspec.height;
        m_framebufferSpecification.width = fbspec.width;
    }

    void Framebuffer::ResizeFramebuffer(uint32_t width, uint32_t height)
    {
        m_framebufferSpecification.width = width;
        m_framebufferSpecification.height = height;

        Invalidate();
    }


    uint32_t& Framebuffer::GetRendererID() { return m_id; }
    uint32_t& Framebuffer::GetDepthAttachment() { return m_depthAttachment; }
    uint32_t& Framebuffer::GetColorAttachment() { return m_colorAttachment; }
    FramebufferSpecification& Framebuffer::GetFramebufferSpecification() { return m_framebufferSpecification; }
}