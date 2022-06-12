
//THE LUNA FRAMEWORK ('TLFW') - Author Note (220516)
/*
	Parts of this projects base API layout has taken inspiration from The Chernos "Game Engine" series. Thank you!
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


static float clrEdit4[4] = { 0.4f, 0.7f, 0.0f, 0.5f };

//Build your own UI here by declairing this function!
void Luna::Application::BuildUI()
{
	//Comment out / remove to not use ImGui
	ImGui::Begin("My own UI!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::ColorEdit4("Color", clrEdit4); //use glm::value_ptr() instead and point to the actual variable. TODO!
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
	Luna::Application app("App"); //Recommended to use a smart ptr instead!

	Entity positionOne;
	positionOne.SetSize(0.5f, 0.3f); //In meters, not pixels
	positionOne.SetPosition(0.0f, 0.0f);
	
	Entity positionTwo;

	//TODO: Add calc to transform units into pixels
	//positionTwo.SetSize(50.0f, 50.0f);
	//positionTwo.SetPosition(300.0f, 150.0f);
	positionTwo.SetSize(0.5f, 0.3f);
	positionTwo.SetPosition(0.5f, 0.5f);

	float lastFrameTime = 0.0f;

	//Un-comment to show GUI examples (ImGui).
	//app.ShowImGuiDemoWindow();

	const char* filePath = "Resources/red.png";
	std::shared_ptr<Luna::Texture> texture = std::make_shared<Luna::Texture>(filePath);
	float speed = 1.0f;
	//Main-loop
	while (app.IsRunning())
	{
		//Calculate delta
		float elapsedTime = app.GetElapsedRuntime();
		Luna::DeltaTime deltaTime = elapsedTime - lastFrameTime;
		lastFrameTime = elapsedTime;

		//Clears screen
		app.Clear(Luna::Colors::Grey);

		glm::vec4 color = BindColorFromValues(clrEdit4);

		app.CheckInputForCamera();

		//Move rectangles
		if (Luna::Input::IsKeyPressed(Luna::Key::W))
		{
			positionOne.anchor.Translation.y += speed * deltaTime;
		}
		else if (Luna::Input::IsKeyPressed(Luna::Key::S))
		{
			positionOne.anchor.Translation.y -= speed * deltaTime;
		}
		if (Luna::Input::IsKeyPressed(Luna::Key::A))
		{
			positionOne.anchor.Translation.x -= speed * deltaTime;
		}
		else if (Luna::Input::IsKeyPressed(Luna::Key::D))
		{
			positionOne.anchor.Translation.x += speed * deltaTime;
		}

		app.Render(texture, positionOne.anchor.GetTransform());			  //Texture
		app.RenderShaderColor(color, positionTwo.anchor.GetTransform());  //Shader color

		//Clears the framebuffer. Flush and repeat, updates window and events
		app.Display();
	}
	std::cout << "Closing window...\n";
}