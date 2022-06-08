#include "Lunapch.h"
#include "Shader.h"

#include<glad/glad.h>

namespace Luna {

    //TODO (For another day): move these to a text file and read them externally.

    const char* vertexShaderSource = "#version 410 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n" //vec3?
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
        "in vec3 color;\n" //vec3?
        "in vec2 texCoord;\n"
        "uniform sampler2D tex0;"
        "void main()\n"
        "{\n"
        //"FragColor = vec4(color, 1.0f);\n"       //clr!!
        "FragColor = texture(tex0, texCoord);\n" //texture
        //"FragColor = {0.0f, 1.0f, 0.0f, 1.0f};\n"  //clr!!
    
        //"FragColor = texture(tex0, texCoord);\n"
        "}\n\0";
    
    //--------------------------------------------------------------------------------

    /*
        if:
            In fragcolor = texture(tex0) -> m_Shader & scale in setdata
    
        else if:
            In fragcolor = texture(scale) -> m_Shader & tex0 in setdata
    */


    //FOR PARTICLES
    const char* vertexShaderSourceClr = "#version 410 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "uniform mat4 scale;\n" //rename into something else
        "void main()\n"
        "{\n"
        "gl_Position = scale * vec4(aPos, 1.0);\n" //MOve down under color & texcoord
        "}\0";
    
    //Fragment Shader source code
    const char* fragmentShaderSourceClr = "#version 410 core\n"
        "layout (location = 0) out vec4 o_Color;\n"
        "uniform vec4 u_Color;\n"
        "void main()\n"
        "{\n"
        "o_Color = u_Color;\n"
        "}\n\0";
    


    //TODO - cleanup this constructor for easier usage later on.
    Shader::Shader(std::string& mode)//const char* vertexFile, const char* fragmentFile)
    {
        if (mode == "clr")
        {
            GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShader, 1, &vertexShaderSourceClr, NULL);
            glCompileShader(vertexShader);

            CompileErrors(vertexShader, "VERTEX");

            //FRAGMENT
            GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShader, 1, &fragmentShaderSourceClr, NULL);
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
        if (mode == "txt")
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

        //GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        //glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        //glCompileShader(vertexShader);
        //
        //CompileErrors(vertexShader, "VERTEX");
        //
        ////FRAGMENT
        //GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        //glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        //glCompileShader(fragmentShader);
        //
        ////new
        //CompileErrors(fragmentShader, "FRAGMENT");
        //
        //m_ID = glCreateProgram();
        //
        //glAttachShader(m_ID, vertexShader);
        //glAttachShader(m_ID, fragmentShader);
        //glLinkProgram(m_ID);
        //
        //CompileErrors(m_ID, "PROGRAM");
        //
        ////Cleanup
        //glDeleteShader(vertexShader);
        //glDeleteShader(fragmentShader);
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

    //TEST! particles
    void Shader::SetShaderColor(glm::vec4 clr)
    {
        //rename, these are NOT members!
        GLuint m_ParticleShader = glGetUniformLocation(m_ID, "u_Color");
        glUniform4fv(m_ParticleShader, 1, glm::value_ptr(clr));
    }

    void Shader::CompileErrors(unsigned int shader, const char* type)
    {
        //TODO
        // - Change these variablenames + add error list.
        // - Move into a switch

        GLint hasCompiled;
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

    // Reads a text file and outputs a string with everything in the text file, doesn't work properly
    std::string GetFileContents(const char* filename)
    {
        std::ifstream in(filename, std::ios::binary);
        if (in)
        {
            std::string path;
            in.seekg(0, std::ios::end);
            path.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&path[0], path.size());
            in.close();
            return(path);
        }
        throw(errno);
    }
}