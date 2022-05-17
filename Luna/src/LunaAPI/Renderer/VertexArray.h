#pragma once

#include "LunaAPI/Renderer/VertexArray.h"
#include "LunaAPI/Renderer/Shader.h"
#include "LunaAPI/Renderer/Buffers.h"

namespace Luna {
	class VertexArray
	{
	public:
		uint32_t m_ID;

	public:
		std::shared_ptr<ElementBuffer> m_ElementBuffer;				
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers; 

		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

		void AddElementBuffer(uint32_t* indices);
		void AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexArray);
	};
}