
//THE LUNA FRAMEWORK ('TLFW') - Author Note (220516)
/*
	A major part of this projects API layout has taken inspiration from The Chernos "Game Engine" series. Thank you!
*/

#include "Luna.h"		 //Contains everything you need!
#include <imgui/imgui.h> //Needed if you want to build your own UI.

struct Entity
{
	Luna::Anchor anchor; //First thing from the Luna API. This is just a matrix with pos, scale and rotation.
	//For game dev, this is what you use and manipulate if you want to (for example) move a texture around.

	void SetPosition(float x, float y)
	{
		anchor.Translation.x = x;
		anchor.Translation.y = y;
	}
	
	void SetSize(float w, float h)
	{
		anchor.Scale.x = w;
		anchor.Scale.y = h;
	}
};

//-------------------------------------------------------
//		   EXAMPLE OF HOW TO IMPLEMENT IMGUI
//-------------------------------------------------------


static float col2[4] = { 0.4f, 0.7f, 0.0f, 0.5f };

//Build your own UI here by overriding this function. Comment out / remove to not use ImGui.
void Luna::Application::BuildUI()
{
	ImGui::Begin("My own UI!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::ColorEdit4("Color", col2);
	ImGui::End();
}

//TODO: Move to renderer later. Here for the example!
glm::vec4 BindColorFromValues(static float clrIn[4])
{
	glm::vec4 clr;
	clr[0] = clrIn[0];
	clr[1] = clrIn[1];
	clr[2] = clrIn[2];
	clr[3] = 1.0f; //Transparency

	return clr;
}

//Here we go!
int main()
{
	std::cout << "Opening new window!\n";
	Luna::Application app("App");


	Entity pos1;
	pos1.SetSize(50.0f, 50.0f);
	pos1.SetPosition(600.0f, 350.0f);
	
	Entity pos2;
	pos2.SetSize(50.0f, 50.0f);
	pos2.SetPosition(300.0f, 150.0f);


	float m_LastFrameTime = 0.0f;

	//Un-comment to show GUI examples (ImGui).
	//app.ShowImGuiDemoWindow();

	std::shared_ptr<Luna::Texture> texture = std::make_shared<Luna::Texture>("D:/dev/LFW_Luna-Framework_Experimental/Resources/blue.png");


	while (app.IsRunning())
	{
		float elapsedTime = app.GetElapsedRuntime();
		Luna::DeltaTime deltaTime = elapsedTime - m_LastFrameTime;
		m_LastFrameTime = elapsedTime;

		app.Clear(Luna::Colors::Grey);


		glm::vec4 clr = BindColorFromValues(col2);

		app.Render(texture, pos1.anchor.GetTransform()); //TEXTURE
		app.RenderShaderColor(clr, pos2.anchor.GetTransform());	   //SHADER

		//Clears the framebuffer. Flush and repeat, updates window and events
		app.Display();
	}
	std::cout << "Closing window...\n";
}