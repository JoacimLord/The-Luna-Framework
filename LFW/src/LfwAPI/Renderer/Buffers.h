#pragma once

typedef unsigned int GLuint;

namespace LFW {

	struct QuadVertex;

	class ElementBuffer
	{
	public:
		ElementBuffer(uint32_t* indices, uint32_t size);
		~ElementBuffer();

		void Bind();
		void Unbind();

	private:
		uint32_t m_id;
	};


	class VertexBuffer
	{

	public:
		VertexBuffer(float* vertices, uint32_t size);
		VertexBuffer(std::vector<QuadVertex>& verticies);
		~VertexBuffer();

		void Bind();
		void Unbind();

	private:
		uint32_t m_id;
	};
}