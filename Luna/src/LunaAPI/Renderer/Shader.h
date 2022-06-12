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

	class Shader
	{
	public:
		Shader(std::string& mode);//const char* vertexFile, const char* fragmentFile);
		~Shader();
		void Bind();   //Remove?
		void Unbind(); //Remove?

		void SetMat4(glm::mat4 matrix, const char* name);
		//void SetMat4(glm::mat4 matrix);
		void SetFlatShaderColor(glm::vec4 clr);


	private:
		void CompileErrors(unsigned int shader, const char* type);

	public:
		GLuint m_ID;
	};

	//Move to a separate "Reader" class
	std::string GetFileContents(const char* filename);
}