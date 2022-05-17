#pragma once

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

typedef unsigned int GLuint;

namespace Luna {

	std::string GetFileContents(const char* filename);

	class Shader
	{
	public:
		GLuint m_ID;

	public:
		Shader();//const char* vertexFile, const char* fragmentFile);
		~Shader();
		void Bind();
		void Unbind();
		void SetMat4(glm::mat4 ModelViewMatrix);

	private:
		void CompileErrors(unsigned int shader, const char* type);
	};
}