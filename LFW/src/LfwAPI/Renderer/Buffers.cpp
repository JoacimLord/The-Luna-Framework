#include "LFWpch.h"
#include "Buffers.h"

#include "Renderer.h"

#include <glad/glad.h>

namespace LFW {

    ElementBuffer::ElementBuffer(uint32_t* indices, uint32_t size)
    {
        glGenBuffers(1, &m_ID);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }

    ElementBuffer::~ElementBuffer()
    {
        glDeleteBuffers(1, &m_ID);
    }

    void ElementBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
    }
    void ElementBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
    {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(std::vector<QuadVertex>& verticies)
    {
        glGenBuffers(1, &m_ID);
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
        glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(QuadVertex), verticies.data(), GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_ID);
    }

    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_ID);
    }

    void VertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}