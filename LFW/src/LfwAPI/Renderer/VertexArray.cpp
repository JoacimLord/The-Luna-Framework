#include "LFWpch.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace LFW {

    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_id);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_id);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(m_id);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }
    void VertexArray::AddElementBuffer(uint32_t* indices)
    {
        m_elementBuffer = std::make_shared<ElementBuffer>(indices, sizeof(indices) * 6);
    }

    void VertexArray::AddVertexBufferTexture(std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        Bind();

        m_elementBuffer->Bind();
        vertexBuffer->Bind();

        //FIRST : -----------------------------------------------------------------
        glEnableVertexAttribArray(0); //index
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
       
        //SECOND : -----------------------------------------------------------------
        glEnableVertexAttribArray(1); //index
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

        //THIRD : -----------------------------------------------------------------
        glEnableVertexAttribArray(2); //index
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

        Unbind();
        m_elementBuffer->Unbind();
        vertexBuffer->Unbind();
    }


    void VertexArray::AddVertexBufferColor(std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        Bind();

        m_elementBuffer->Bind();
        vertexBuffer->Bind();

        //FIRST : -----------------------------------------------------------------
        glEnableVertexAttribArray(0); //index
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

        Unbind();
        m_elementBuffer->Unbind();
        vertexBuffer->Unbind();
    }
}