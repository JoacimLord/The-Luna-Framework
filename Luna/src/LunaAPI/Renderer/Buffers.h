#pragma once

namespace Luna {

	class ElementBuffer
	{
	public:
		uint32_t m_ID;

	public:
		ElementBuffer(uint32_t* indices, uint32_t size);
		~ElementBuffer();

		void Bind();
		void Unbind();
	};

	class VertexBuffer
	{
	public:
		uint32_t m_ID;

	public:
		VertexBuffer(float* vertices, uint32_t size);
		~VertexBuffer();

		void Bind();
		void Unbind();
	};
}