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
        if (sprite.texture)
        {
            s_RendererData.TextureVertexArray->AddElementBuffer(QuadData::quadInds);
            QuadMesh quadMesh;
            QuadData::SetQuadData(quadMesh);
            std::shared_ptr<VertexBuffer> VBO = std::make_shared<VertexBuffer>(quadMesh.verticies);
            s_RendererData.TextureVertexArray->AddVertexBufferTexture(VBO);


            s_RendererData.TextureShader->Bind();
            s_RendererData.TextureShader->SetMat4(s_OrthoCam.viewProjMatrix, "u_ViewProj");
            s_RendererData.TextureShader->SetMat4(sprite.GetTransform(), "scale");

            //Bind the texture and draw
            glBindTexture(GL_TEXTURE_2D, sprite.texture->id);
            DrawElements(s_RendererData.TextureVertexArray, s_RendererData.QUAD_SIZE);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        else
        {
            s_RendererData.ColorVertexArray->AddElementBuffer(QuadData::quadInds);

            QuadMesh quadMesh;
            QuadData::SetQuadData(quadMesh);
            std::shared_ptr<VertexBuffer> VBO = std::make_shared<VertexBuffer>(quadMesh.verticies);
            s_RendererData.ColorVertexArray->AddVertexBufferColor(VBO);

            s_RendererData.ColorShader->Bind();
            s_RendererData.ColorShader->SetMat4(s_OrthoCam.viewProjMatrix, "u_ViewProj");
            s_RendererData.ColorShader->SetMat4(sprite.GetTransform(), "scale");

            //Sumbit a color and draw
            s_RendererData.ColorShader->SetVec4(sprite.color);
            DrawElements(s_RendererData.ColorVertexArray, s_RendererData.QUAD_SIZE);
        }
    }


    void Renderer::DrawFromSpritesheet(Spritesheet& spriteSheet, int textureWidth, int textureHeight, int spriteWidth, int spriteHeight, int numberofSprites, int spacing)
    {
        // TODO: Fix this
        if (spriteSheet.loaded)
        {
            for (size_t i = 0; i < spriteSheet.sprites.size(); i++)
            {
                s_RendererData.TextureVertexArray->AddElementBuffer(QuadData::quadInds);

                std::shared_ptr<VertexBuffer> VBO = std::make_shared<VertexBuffer>(spriteSheet.quads[i].verticies);
                s_RendererData.TextureVertexArray->AddVertexBufferTexture(VBO);

                s_RendererData.TextureShader->Bind();
                s_RendererData.TextureShader->SetMat4(s_OrthoCam.viewProjMatrix, "u_ViewProj");
                s_RendererData.TextureShader->SetMat4(spriteSheet.sprites[i].GetTransform(), "scale");
                glBindTexture(GL_TEXTURE_2D, spriteSheet.sprites[i].texture->id);
                DrawElements(s_RendererData.TextureVertexArray, s_RendererData.QUAD_SIZE);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
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