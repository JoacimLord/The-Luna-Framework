#include "Lunapch.h"
#include "Renderer.h"

#include <glad/glad.h>
#include <LunaAPI/Core/Input.h>

namespace Luna {
    
    const uint32_t QUAD_SIZE = 6;
 
    //OLD
    //struct Camera 
    //{
    //    glm::mat4 proj = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
    //    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)); //5.0??
    //
    //    glm::mat4 GetProjection()
    //    {
    //        return proj;
    //    
    //    }
    //
    //    glm::mat4 GetView()
    //    {
    //        return view;
    //    }
    //};

    struct RendererData
    {
        //Rename someday :>
        //Shader & VA for !textures
        std::shared_ptr<VertexArray> ClrVA;
        std::shared_ptr<Shader> ClrShader;


        //Shader & VA for textures
        std::shared_ptr<VertexArray> VertexArray;
        std::shared_ptr<Shader> Shader;
        std::array<std::shared_ptr<Texture>, 32> TextureSlots;

        uint32_t TextureIndex = 0;
        Statistics Stats;
    };

    //static Camera s_Camera;
    static RendererData s_RendererData;
   
    float l = -1.6f;
    float r = 1.6f;
    float b = -0.9f;
    float t = 0.9f;
    static OrthoCam s_OrthoCam(l, r, b, t);

    //Do nothing? Remove and change to default?
    Renderer::Renderer()
    {
    }

    //Do nothing? Default?
    Renderer::~Renderer()
    {
    }

    void Renderer::Init()
    {
        //can const these & move them
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

        //Abstract away or is it to confusing otherwise?
        std::shared_ptr<VertexBuffer> VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));

        s_RendererData.VertexArray->AddElementBuffer(indices);
        s_RendererData.VertexArray->AddVertexBuffer(VBO);

        //Clr
        s_RendererData.ClrVA->AddElementBuffer(indices);
        s_RendererData.ClrVA->AddVertexBuffer(VBO);
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

 





   
  

    void Renderer::Draw(std::shared_ptr<Texture>& texture, const glm::mat4& entityTransform)
    {
        //This is for NO camera, maybe better for a framework?
       //glm::mat4 ModelViewMatrix = s_Camera.GetProjection() * s_Camera.GetView() * entityTransform;      
       //s_RendererData.Shader->SetMat4(ModelViewMatrix); //THIS WORKS, just needs to be done once?
        

        //s_OrthoCam.SetPos({ 1.0f, 0.0f, 0.0f });
        

       //Change to GetViewProj() later on. Move these two to a "SetCamera()" function or something!
       s_RendererData.Shader->SetMat4(s_OrthoCam.viewProjMatrix, "u_ViewProj"); //THIS WORKS, just needs to be done once?
       s_RendererData.Shader->SetMat4(entityTransform, "scale"); //Every time we submit we need to do THIS


        s_RendererData.TextureSlots[s_RendererData.TextureIndex] = texture;
        s_RendererData.TextureIndex++;

        glBindTexture(GL_TEXTURE_2D, texture->id);
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

    //Added 220526
    void Renderer::OnWindowResize(float width, float height)
    {
        std::cout << "glViewport changing\n";
        glViewport(0, 0, width, height);
    }
     

    void Renderer::DrawParticleTest(glm::vec4 clr, const glm::mat4& entityTransform)
    { 
        //glm::mat4 ModelViewMatrix = s_Camera.GetProjection() * s_Camera.GetView() * pos;
        s_RendererData.Shader->SetMat4(s_OrthoCam.viewProjMatrix, "u_ViewProj"); //THIS WORKS, just needs to be done once?
        s_RendererData.Shader->SetMat4(entityTransform, "scale"); //Every time we submit we need to do THIS

       // s_RendererData.ClrShader->SetMat4(ModelViewMatrix, "scale");
       // s_RendererData.ClrShader->SetMat4(pos, "scale"); //Every time we submit we need to do THIS

        s_RendererData.ClrShader->Bind();
        
        s_RendererData.ClrShader->SetShaderColor(clr);
        DrawElements(s_RendererData.ClrVA, QUAD_SIZE);
    }

    //(Fix and chain over to application.cpp/h)
    void Renderer::BindColorFromValues(glm::vec4 clrIn, static float clrOut[4])
    {
        clrIn[0] = clrOut[0];
        clrIn[1] = clrOut[1];
        clrIn[2] = clrOut[2];
        clrIn[3] = 1.0f; //Transparency
    }

    Statistics Renderer::GetDrawCalls()
    {
        return s_RendererData.Stats;
    }
}