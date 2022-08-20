#pragma once

namespace LFW {

	class ElementBuffer
	{
	public:
		ElementBuffer(uint32_t* indices, uint32_t size);
		~ElementBuffer();

		void Bind();
		void Unbind();

	private:
		uint32_t m_ID;
	};

	class VertexBuffer
	{

	public:
		VertexBuffer(float* vertices, uint32_t size);
		~VertexBuffer();

		void Bind();
		void Unbind();

	private:
		uint32_t m_ID;
	};
}