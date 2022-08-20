#include "LFWpch.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <LfwAPI/Core/Input.h>

namespace LFW {
    
    const uint32_t QUAD_SIZE = 6;
 
    struct RendererData
    {
        std::shared_ptr<VertexArray> ClrVA;
        std::shared_ptr<Shader> ClrShader;

        std::shared_ptr<VertexArray> VertexArray;
        std::shared_ptr<Shader> Shader;
    };

    static RendererData s_RendererData;
   
    static float l = -1.6f;
    static float r = 1.6f;
    static float b = -0.9f;
    static float t = 0.9f;
    static OrthoCam s_OrthoCam(l, r, b, t);

    void Renderer::Init()
    {
        std::string txtMode = "txt";
        std::string clrtMode = "clr";

        OpenGLEnables();

        s_RendererData.VertexArray = std::make_shared<VertexArray>();
        s_RendererData.Shader = std::make_shared<Shader>(txtMode);

        //Clr
        s_RendererData.ClrVA = std::make_shared<VertexArray>();
        s_RendererData.ClrShader = std::make_shared<Shader>(clrtMode);

        GLfloat vertices[] =
        {
            //CORDINATES				//COLORS		//TEXCORDS
           -0.5f, -0.5f, 0.0f, 1.0f,	0.0f, 0.0f,		 0.0f,	0.0f,
            0.5f, -0.5f, 0.0f, 1.0f,	1.0f, 0.0f,		 1.0f,	0.0f,
            0.5f,  0.5f, 0.0f, 1.0f,	0.0f, 1.0f,		 1.0f,	1.0f,
           -0.5f,  0.5f, 0.0f, 1.0f,	1.0f, 1.0f,		 0.0f,	1.0f
        };

        GLuint indices[] =
        {
            0, 2, 1,
            0, 3, 2
        };

        std::shared_ptr<VertexBuffer> VBOtexture = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        std::shared_ptr<VertexBuffer> VBOcolor = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));

        s_RendererData.VertexArray->AddElementBuffer(indices);
        s_RendererData.VertexArray->AddVertexBufferTexture(VBOtexture);

        //Clr
        s_RendererData.ClrVA->AddElementBuffer(indices);
        s_RendererData.ClrVA->AddVertexBufferColor(VBOcolor);
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::ClearColor(float r, float g, float b, float transparent)
    {
        
        glClearColor(r, g, b, transparent);
    }

    void Renderer::ClearFrame(float r, float g, float b, float transparent)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(r, g, b, transparent);
    }

    OrthoCam Renderer::GetCamera()
    {
        return s_OrthoCam;
    }

    void Renderer::SetCameraPosition(const glm::vec3 temppos)
    {
        s_OrthoCam.SetPos(temppos);
    }

    glm::vec3 Renderer::GetCameraPosition()
    {
        return GetCamera().GetPos();
    }

    void Renderer::Draw(Sprite& sprite)
    {
        //TODO: Move the camera setup into it's own function
        if (sprite.texture)
        {
            s_RendererData.Shader->Bind();
            s_RendererData.Shader->SetMat4(s_OrthoCam.viewProjMatrix, "u_ViewProj");
            s_RendererData.Shader->SetMat4(sprite.anchor.GetTransform(), "scale");   

            //Bind the texture and draw
            glBindTexture(GL_TEXTURE_2D, sprite.texture->id);
            DrawElements(s_RendererData.VertexArray, QUAD_SIZE);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        else
        {
            s_RendererData.ClrShader->Bind();
            s_RendererData.ClrShader->SetMat4(s_OrthoCam.viewProjMatrix, "u_ViewProj");
            s_RendererData.ClrShader->SetMat4(sprite.anchor.GetTransform(), "scale");

            //Sumbit a color and draw
            s_RendererData.ClrShader->SetVec4(sprite.color);
            DrawElements(s_RendererData.ClrVA, QUAD_SIZE);
        }
    }

    void Renderer::DrawElements(std::shared_ptr<VertexArray>& vertexArray, uint32_t size)
    {
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
        vertexArray->Unbind();
    }

    void Renderer::OpenGLEnables()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);

    }

    void Renderer::OnWindowResize(float width, float height)
    {
        std::cout << "glViewport changing\n";
        glViewport(0, 0, width, height);
    }
}