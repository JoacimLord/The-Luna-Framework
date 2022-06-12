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

//Change the code spec to be the same as in other files, 
/*
	- public functions  (1)
	- private functions (2)
	- public variables  (3)
	- private variables (4)
*/