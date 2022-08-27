#include "LFWpch.h"
#include "Buffers.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace LFW {

    ElementBuffer::ElementBuffer(uint32_t* indices, uint32_t size)
    {
        glGenBuffers(1, &m_id);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }

    ElementBuffer::~ElementBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void ElementBuffer::Bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }
    void ElementBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::VertexBuffer(std::vector<QuadVertex>& verticies)
    {
        glGenBuffers(1, &m_id);
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
        glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(QuadVertex), verticies.data(), GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &m_id);
    }

    void VertexBuffer::Bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    void VertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}