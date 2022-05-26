#include "Lunapch.h"
#include "Renderer.h"

#include <glad/glad.h>

namespace Luna {
    
    const uint32_t QUAD_SIZE = 6;
 
    struct Camera 
    {
        glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //5.0??

        glm::mat4 GetProjection()
        {
            return proj;
        
        }

        glm::mat4 GetView()
        {
            return view;
        }
    };

    struct RendererData
    {
        std::shared_ptr<VertexArray> VertexArray;
        std::shared_ptr<Shader> Shader;
        std::array<std::shared_ptr<Texture>, 32> TextureSlots;

        uint32_t TextureIndex = 0;
        Statistics Stats;
    };

    static Camera s_Camera;
    static RendererData s_RendererData;


    Renderer::Renderer()
    {
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::Init()
    {
        OpenGLEnables();
        s_RendererData.VertexArray = std::make_shared<VertexArray>();
        s_RendererData.Shader = std::make_shared<Shader>();

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

        std::shared_ptr<VertexBuffer> VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));

        s_RendererData.VertexArray->AddElementBuffer(indices);
        s_RendererData.VertexArray->AddVertexBuffer(VBO);
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
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

    void Renderer::Draw(std::shared_ptr<Texture>& texture, glm::mat4 entityTransform)
    {
        glm::mat4 ModelViewMatrix = s_Camera.GetProjection() * s_Camera.GetView() * entityTransform;
        s_RendererData.Shader->SetMat4(ModelViewMatrix);
       
        s_RendererData.TextureSlots[s_RendererData.TextureIndex] = texture;
        s_RendererData.TextureIndex++;

        glBindTexture(GL_TEXTURE_2D, texture->id);
        s_RendererData.Shader->Bind();

        DrawElements(s_RendererData.VertexArray, QUAD_SIZE);
        
        s_RendererData.TextureIndex = 0;
 
        glBindTexture(GL_TEXTURE_2D, 0);

        s_RendererData.Stats.DrawCalls++;
    }

    void Renderer::Draw(Texture texture, glm::mat4 entityTransform)
    {
        glm::mat4 ModelViewMatrix = s_Camera.GetProjection() * s_Camera.GetView() * entityTransform;
        s_RendererData.Shader->SetMat4(ModelViewMatrix);

        glBindTexture(GL_TEXTURE_2D, texture.id);
        s_RendererData.Shader->Bind();

        DrawElements(s_RendererData.VertexArray, QUAD_SIZE);
        s_RendererData.TextureIndex = 0;

        glBindTexture(GL_TEXTURE_2D, 0);
        s_RendererData.Stats.DrawCalls++;
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

    //NEW!! - 220526
    void Renderer::OnWindowResize(float width, float height)
    {
        std::cout << "glViewport changing\n";
        glViewport(0, 0, width, height);
    }



    Statistics Renderer::GetDrawCalls()
    {
        return s_RendererData.Stats;
    }
}