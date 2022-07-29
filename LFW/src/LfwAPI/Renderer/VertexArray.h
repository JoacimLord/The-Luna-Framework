#pragma once

#include "LfwAPI/Renderer/VertexArray.h"
#include "LfwAPI/Renderer/Shader.h"
#include "LfwAPI/Renderer/Buffers.h"

namespace LFW {
	class VertexArray
	{
	public:
		std::shared_ptr<ElementBuffer> m_ElementBuffer;				
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers; 

		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

		void AddElementBuffer(uint32_t* indices);
		void AddVertexBufferTexture(std::shared_ptr<VertexBuffer>& vertexBuffer);
		void AddVertexBufferColor(std::shared_ptr<VertexBuffer>& vertexBuffer);

	public:
		uint32_t m_ID;
	};
}