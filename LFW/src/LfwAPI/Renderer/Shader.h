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

namespace LFW {

	class Shader
	{
	public:
		Shader(std::string& mode);
		~Shader();
		void Bind();
		void Unbind();

		//Sets glUniformMatrix4fv
		void SetMat4(glm::mat4 matrix, const char* name);

		//Sets glUniform4fv
		void SetVec4(glm::vec4 clr);


	private:
		void CompileErrors(unsigned int shader, const char* type);

	private:
		GLuint m_id;
	};

	//Move to a separate "Reader" class
	std::string GetFileContents(const char* filename);
}