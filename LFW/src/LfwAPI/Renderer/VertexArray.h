#pragma once

#include "LfwAPI/Renderer/VertexArray.h"
#include "LfwAPI/Renderer/Shader.h"
#include "LfwAPI/Renderer/Buffers.h"

namespace LFW {
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

		void AddElementBuffer(uint32_t* indices);
		void AddVertexBufferTexture(std::shared_ptr<VertexBuffer>& vertexBuffer);
		void AddVertexBufferColor(std::shared_ptr<VertexBuffer>& vertexBuffer);

	private:
		std::shared_ptr<ElementBuffer> m_elementBuffer;
		std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
		uint32_t m_id;
	};
}