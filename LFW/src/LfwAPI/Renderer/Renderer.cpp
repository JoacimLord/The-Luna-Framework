#include "LFWpch.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <LfwAPI/Core/Input.h>

namespace LFW {
    
    struct RendererData
    {
        const uint32_t QUAD_SIZE = 6;

        //Color
        std::shared_ptr<VertexArray> colorVertexArray;
        std::shared_ptr<Shader> colorShader;

        //Single texture
        std::shared_ptr<VertexArray> textureVertexArray;
        std::shared_ptr<Shader> textureShader;

        //Spritesheet
        std::shared_ptr<VertexArray> spritesheetTextureVertexArray;
        std::shared_ptr<Shader> spritesheetTextureShader;
    };

    static RendererData s_rendererData;
   
    //TODO: Fix this
    static float l = -1.6f;
    static float r = 1.6f;
    static float b = -0.9f;
    static float t = 0.9f;
    static OrthographicCamera s_orthoCam(l, r, b, t);

    void Renderer::Init()
    {
        std::string textureShaderFile = "txt";
        std::string colorShaderFile = "clr";

        OpenGLEnables();

        //----------------------------------------------------------------------
        // Init VAOs & Shaders
        //----------------------------------------------------------------------

        //Texture
        s_rendererData.textureVertexArray = std::make_shared<VertexArray>();
        s_rendererData.textureShader = std::make_shared<Shader>(textureShaderFile);

        //Spritesheet Textures
        s_rendererData.spritesheetTextureVertexArray = std::make_shared<VertexArray>();
        s_rendererData.spritesheetTextureShader = std::make_shared<Shader>(textureShaderFile);

        //Color
        s_rendererData.colorVertexArray = std::make_shared<VertexArray>();
        s_rendererData.colorShader = std::make_shared<Shader>(colorShaderFile);


        //----------------------------------------------------------------------
        //Indicies
        //----------------------------------------------------------------------

        //Add indicies to single texture quads
        s_rendererData.textureVertexArray->AddElementBuffer(QuadData::quadInds);

        //Add indicies to single spritesheet quads
        s_rendererData.spritesheetTextureVertexArray->AddElementBuffer(QuadData::quadInds);

        //Add indicies to single color quads
        s_rendererData.colorVertexArray->AddElementBuffer(QuadData::quadInds);


        //----------------------------------------------------------------------
        //Set VAOs
        //----------------------------------------------------------------------

        QuadMesh quadMesh;
        QuadData::SetQuadData(quadMesh);
        std::shared_ptr<VertexBuffer> VBO = std::make_shared<VertexBuffer>(quadMesh.verticies);

        s_rendererData.textureVertexArray->AddVertexBufferTexture(VBO);
        //s_RendererData.SpritesheetTextureVertexArray->AddVertexBufferTexture(VBO);
        s_rendererData.colorVertexArray->AddVertexBufferTexture(VBO);
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
        return s_orthoCam;
    }

    void Renderer::SetCameraPosition(const glm::vec3 temppos)
    {
        s_orthoCam.SetPosition(temppos);
    }

    glm::vec3 Renderer::GetCameraPosition()
    {
        return GetCamera().GetPosition();
    }

    glm::vec2 Renderer::WorldToScreenPoint(glm::vec2 screenCoords, float screenW, float screenH)
    {
        return s_orthoCam.WorldToScreenPoint(screenCoords, screenW, screenH);
    }

    glm::vec2 Renderer::ScreenToWorldPoint(float screenW, float screenH)
    {
        return s_orthoCam.ScreenToWorldPoint(screenW, screenH);
    }

    void Renderer::Render(Sprite& sprite)
    {
        if (sprite.texture)
        {
            s_rendererData.textureShader->Bind();
            s_rendererData.textureShader->SetMat4(s_orthoCam.viewProjMatrix, "u_ViewProj");
            s_rendererData.textureShader->SetMat4(sprite.GetTransform(), "scale");

            //Bind the texture and draw
            glBindTexture(GL_TEXTURE_2D, sprite.texture->id);
            DrawElements(s_rendererData.textureVertexArray, s_rendererData.QUAD_SIZE);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        else
        {
            s_rendererData.colorShader->Bind();
            s_rendererData.colorShader->SetMat4(s_orthoCam.viewProjMatrix, "u_ViewProj");
            s_rendererData.colorShader->SetMat4(sprite.GetTransform(), "scale");

            //Sumbit a color and draw
            s_rendererData.colorShader->SetVec4(sprite.color);
            DrawElements(s_rendererData.colorVertexArray, s_rendererData.QUAD_SIZE);
        }
    }


    void Renderer::RenderFromSpritesheet(Spritesheet& spritesheet, int index)
    {
        /* TODO !!!!!! */
        //Comment this, has to be done to replace coords
        if (spritesheet.loaded)
        {
            QuadVertex quadVerts[] =
            {
                QuadVertex{ glm::vec3(-0.5f, -0.5f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f),  spritesheet.textureCoords[index].coords[0] },
                QuadVertex{ glm::vec3( 0.5f, -0.5f, 0.0f),  glm::vec3(1.0f, 1.0f, 0.0f),  spritesheet.textureCoords[index].coords[1] },
                QuadVertex{ glm::vec3( 0.5f,  0.5f, 0.0f),  glm::vec3(1.0f, 0.0f, 1.0f),  spritesheet.textureCoords[index].coords[2] },
                QuadVertex{ glm::vec3(-0.5f,  0.5f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f),  spritesheet.textureCoords[index].coords[3] },
            };

            //Set the verticies of the quads and add to vector
            std::vector <QuadVertex> verts(quadVerts, quadVerts + sizeof(quadVerts) / sizeof(QuadVertex));
            QuadMesh quadMesh;
            quadMesh.verticies = verts;

            std::shared_ptr<VertexBuffer> VBO = std::make_shared<VertexBuffer>(quadMesh.verticies);
            s_rendererData.spritesheetTextureVertexArray->AddVertexBufferTexture(VBO);

            for (size_t i = 0; i < spritesheet.sprites.size(); i++)
            {
                s_rendererData.textureShader->Bind();
                s_rendererData.textureShader->SetMat4(s_orthoCam.viewProjMatrix, "u_ViewProj");
                s_rendererData.textureShader->SetMat4(spritesheet.sprites[i].GetTransform(), "scale");
                glBindTexture(GL_TEXTURE_2D, spritesheet.spritesheet->id);
                DrawElements(s_rendererData.spritesheetTextureVertexArray, s_rendererData.QUAD_SIZE);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }
    }

    void Renderer::RenderInstanced(Batch& batch, int amount)
    {
        for (int i = 0; i < amount; i++)
        {
            //Translates the sprites
            glm::vec2 newPosition = glm::vec2(batch.sprites[0].GetPosition());
            newPosition.x = i * batch.sprites[0].GetAnchor().scale.x;
            batch.sprites[0].SetPosition(newPosition.x, newPosition.y);

            s_rendererData.textureShader->Bind();
            s_rendererData.textureShader->SetMat4(s_orthoCam.viewProjMatrix, "u_ViewProj");
            s_rendererData.textureShader->SetMat4(batch.sprites[0].GetTransform(), "scale");

            //Bind the instanced textures and draw
            glBindTexture(GL_TEXTURE_2D, batch.sprites[0].texture->id);
            DrawElementsInstanced(s_rendererData.textureVertexArray, s_rendererData.QUAD_SIZE);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }


    void Renderer::DrawElements(std::shared_ptr<VertexArray>& vertexArray, uint32_t size)
    {
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
        vertexArray->Unbind();
    }

    void Renderer::DrawElementsInstanced(std::shared_ptr<VertexArray>& vertexArray, uint32_t size)
    {
        vertexArray->Bind();
        glDrawElementsInstanced(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0, 1);
        vertexArray->Unbind();
    }

    void Renderer::OpenGLEnables()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //This disabled transparency in textures
        //glEnable(GL_DEPTH_TEST);
    }

    void Renderer::OnWindowResize(float width, float height)
    {
        std::cout << "glViewport changing\n";
        glViewport(0, 0, width, height);

        s_orthoCam.OnResize(width, height);
    }
}