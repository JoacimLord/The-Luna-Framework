#pragma once

//NEW----------------------------------
typedef unsigned int GLuint;
//NEW----------------------------------
namespace LFW {

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

	struct QuadVertex;

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