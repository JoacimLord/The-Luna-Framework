#include "LFWpch.h"
#include "VertexArray.h"

#include <glad/glad.h>

namespace LFW {

    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_ID);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &m_ID);
    }

    void VertexArray::Bind()
    {
        glBindVertexArray(m_ID);
    }

    void VertexArray::Unbind()
    {
        glBindVertexArray(0);
    }
    void VertexArray::AddElementBuffer(uint32_t* indices)
    {
        m_ElementBuffer = std::make_shared<ElementBuffer>(indices, sizeof(indices) * 6);
    }

    void VertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        Bind();

        m_ElementBuffer->Bind();
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
        m_ElementBuffer->Unbind();
        vertexBuffer->Unbind();
    }
}