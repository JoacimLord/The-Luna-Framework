
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

//Build your own UI here by overriding this function. Comment out / remove to not use ImGui.
void Luna::Application::BuildUI()
{
	ImGui::Begin("My own UI!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

//Here we go!
int main()
{
	std::cout << "Opening new window!\n";
	Luna::Application app("App");

	//Abstraction in progress, how to load textures.
	std::shared_ptr<Luna::Texture> backdrop = std::make_shared<Luna::Texture>("");
	std::shared_ptr<Luna::Texture> red = std::make_shared<Luna::Texture>("");

	Entity bg;
	bg.SetSize(1500.0f, 800.0f);
	bg.SetPosition(600.0f, 350.0f);

	Entity square;
	square.SetSize(50.0f, 50.0f);
	square.SetPosition(600.0f, 350.0f);
	
	float m_LastFrameTime = 0.0f;

	//Un-comment to show GUI examples (ImGui).
	//app.ShowImGuiDemoWindow();

	while (app.IsRunning())
	{
		float elapsedTime = app.GetElapsedRuntime();
		Luna::DeltaTime deltaTime = elapsedTime - m_LastFrameTime;
		m_LastFrameTime = elapsedTime;

		//Input scope
		{
			if (Luna::Input::IsKeyPressed(Luna::Key::Z))
			{
				//Do something
			}
			else if (Luna::Input::IsKeyPressed(Luna::Key::X))
			{
				//Do something else
			}
		}


		//Clears screen and sets the framebuffer. Choose a pre-defined color or your own float values
		//app.Clear(1.0f, 0.0f, 1.0f, 1.0f);
		app.Clear(Luna::Colors::Pink);
		//Takes in a texture and anchor/transform (position and scale)
		//app.Render(backdrop, bg.anchor.GetTransform());
		//app.Render(red, square.anchor.GetTransform());
		
		//Clears the framebuffer
		app.Display();

		//Flush and repeat, updates window and events
		app.Update();
	}
	std::cout << "Closing window...\n";
}