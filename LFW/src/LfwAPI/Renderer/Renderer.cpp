#include "LFWpch.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <LfwAPI/Core/Input.h>

namespace LFW {
    
    struct RendererData
    {
        const uint32_t QUAD_SIZE = 6;
        std::shared_ptr<VertexArray> ColorVertexArray;
        std::shared_ptr<Shader> ColorShader;

        std::shared_ptr<VertexArray> TextureVertexArray;
        std::shared_ptr<Shader> TextureShader;
    };

    static RendererData s_RendererData;
   
    //TODO: Fix this
    static float l = -1.6f;
    static float r = 1.6f;
    static float b = -0.9f;
    static float t = 0.9f;
    static OrthographicCamera s_OrthoCam(l, r, b, t);

    void Renderer::Init()
    {
        std::string TextureShaderFile = "txt";
        std::string ColorShaderFile = "clr";

        OpenGLEnables();

        //Texture
        s_RendererData.TextureVertexArray = std::make_shared<VertexArray>();
        s_RendererData.TextureShader = std::make_shared<Shader>(TextureShaderFile);

        //Color
        s_RendererData.ColorVertexArray = std::make_shared<VertexArray>();
        s_RendererData.ColorShader = std::make_shared<Shader>(ColorShaderFile);

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

        s_RendererData.TextureVertexArray->AddElementBuffer(indices);
        s_RendererData.TextureVertexArray->AddVertexBufferTexture(VBOtexture);

        //Clr
        s_RendererData.ColorVertexArray->AddElementBuffer(indices);
        s_RendererData.ColorVertexArray->AddVertexBufferColor(VBOcolor);
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::ClearColor(float r, float g, float b, float transparent)
    {
        
        glClearColor(r, g, b, transparent);
    }

    OrthographicCamera Renderer::GetCamera()
    {
        return s_OrthoCam;
    }

    void Renderer::SetCameraPosition(const glm::vec3 temppos)
    {
        s_OrthoCam.SetPosition(temppos);
    }

    glm::vec3 Renderer::GetCameraPosition()
    {
        return GetCamera().GetPosition();
    }

    glm::vec2 Renderer::WorldToScreenPoint(glm::vec2 screenCoords, float screenW, float screenH)
    {
        return s_OrthoCam.WorldToScreenPoint(screenCoords, screenW, screenH);
    }

    glm::vec2 Renderer::ScreenToWorldPoint(float screenW, float screenH)
    {
        return s_OrthoCam.ScreenToWorldPoint(screenW, screenH);
    }

    void Renderer::Draw(Sprite& sprite)
    {
        //TODO: Move the camera setup into it's own function
        if (sprite.texture)
        {
            s_RendererData.TextureShader->Bind();
            s_RendererData.TextureShader->SetMat4(s_OrthoCam.viewProjMatrix, "u_ViewProj");
            s_RendererData.TextureShader->SetMat4(sprite.anchor.GetTransform(), "scale");   

            //Bind the texture and draw
            glBindTexture(GL_TEXTURE_2D, sprite.texture->id);
            DrawElements(s_RendererData.TextureVertexArray, s_RendererData.QUAD_SIZE);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        else
        {
            s_RendererData.ColorShader->Bind();
            s_RendererData.ColorShader->SetMat4(s_OrthoCam.viewProjMatrix, "u_ViewProj");
            s_RendererData.ColorShader->SetMat4(sprite.anchor.GetTransform(), "scale");

            //Sumbit a color and draw
            s_RendererData.ColorShader->SetVec4(sprite.color);
            DrawElements(s_RendererData.ColorVertexArray, s_RendererData.QUAD_SIZE);
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

        s_OrthoCam.OnResize(width, height);
    }
}