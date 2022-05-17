#include "Lunapch.h"
#include "Shader.h"

#include<glad/glad.h>

namespace Luna {

    const char* vertexShaderSource = "#version 410 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "layout (location = 2) in vec2 aTex;\n"
        "out vec3 color;\n"
        "out vec2 texCoord;\n"
        "uniform mat4 scale;\n" //rename into something else
        "void main()\n"
        "{\n"
        //"gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);\n"
        //"gl_Position = vec4(aPos, 1.0);\n"
        "gl_Position = scale * vec4(aPos, 1.0);\n" //MOve down under color & texcoord
        "color = aColor;\n" //NOT NEEDED
        "texCoord = aTex;\n"
        "}\0";

    //Fragment Shader source code
    const char* fragmentShaderSource = "#version 410 core\n"
        "out vec4 FragColor;\n"
        "in vec3 color;\n"
        "in vec2 texCoord;\n"
        "uniform sampler2D tex0;"
        "void main()\n"
        "{\n"
        "FragColor = texture(tex0, texCoord);\n"
        //"FragColor = vec4(color, 1.0f);\n"
        //"FragColor = texture(tex0, texCoord);\n"
        "}\n\0";

    //--------------------------------------------------------------------------------

    /*
        if:
            In fragcolor = texture(tex0) -> m_Shader & scale in setdata
    
        else if:
            In fragcolor = texture(scale) -> m_Shader & tex0 in setdata
    */

    Shader::Shader()//const char* vertexFile, const char* fragmentFile)
    {
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        CompileErrors(vertexShader, "VERTEX");

        //FRAGMENT
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        //new
        CompileErrors(fragmentShader, "FRAGMENT");

        m_ID = glCreateProgram();

        glAttachShader(m_ID, vertexShader);
        glAttachShader(m_ID, fragmentShader);
        glLinkProgram(m_ID);

        CompileErrors(m_ID, "PROGRAM");

        //Cleanup
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_ID);
    }

    void Shader::Bind()
    {
        glUseProgram(m_ID);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    void Shader::SetMat4(glm::mat4 ModelViewMatrix)
    {
        GLuint uniID = glGetUniformLocation(m_ID, "scale");
        glUniformMatrix4fv(uniID, 1, GL_FALSE, glm::value_ptr(ModelViewMatrix));
    }

    void Shader::CompileErrors(unsigned int shader, const char* type)
    {
        GLint hasCompiled;

        // Character array to store error message in
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &hasCompiled);
            if (hasCompiled == GL_FALSE)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n" << infoLog << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &hasCompiled);
            if (hasCompiled == GL_FALSE)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "SHADER_LINKING_ERROR for:" << type << "\n" << infoLog << std::endl;
            }
        }
    }

    // Reads a text file and outputs a string with everything in the text file (From Victor Gorbans youtube series)
    std::string GetFileContents(const char* filename)
    {
        std::ifstream in(filename, std::ios::binary);
        if (in)
        {
            std::string contents;
            in.seekg(0, std::ios::end);
            contents.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&contents[0], contents.size());
            in.close();
            return(contents);
        }
        throw(errno);
    }
}