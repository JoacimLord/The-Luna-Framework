
//LUNA FRAMEWORK (LFW) - Author Note (220516)
/*
	A major part of this projects API has taken inspiration from The Chernos "Game Engine" series.
	I've changed a whole lot but a big thank you for the starting point, the thinking process and the structural influence of the project.

	Examples on how to use the API in your own development. Just include "Luna.h" in your source file and you're good to go!

	This framework is only aimed for development on Windows for now and can only render 2D graphics.
	The project is in a very early phase and therefore it has alot of pasta code without much optimisation, but it works.

	The project uses OpenGL and ImGui and is based on my other project Luna Engine (Same API but with a working and intergrated IU / Editor and is based around game development).
	The goal with this project is to move away from game dev and be a suitable framework for all kinds of GUI based apps.

	Thank you for using my framework, have a lovely day<3
	//Joacim (Jooko94)

	(This project was last edited on 220517).
*/

//-------------------------------------------------------
//					WHAT TO INCLUDE
//-------------------------------------------------------

#include "Luna.h"		 //Contains everything you need!
#include <imgui/imgui.h> //Needed if you want to build your own UI.


//-------------------------------------------------------
//		   EXAMPLE OF HOW TO BUILD A BASIC OBJ
//-------------------------------------------------------

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
	Luna::Application app("App"); //For this example the app is on the heap. Do as you please (but don't forget to delete :))

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
		float elapsedTime = app.GetElapesedRuntime();
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

		//Clears screen and sets the framebuffer
		app.Clear(1.0f, 0.0f, 1.0f, 1.0f);

		//Takes in a texture and anchor/transform (position and scale)
		app.Render(backdrop, bg.anchor.GetTransform());
		app.Render(red, square.anchor.GetTransform());
		
		//Clears the framebuffer
		app.Display();

		//Flush and repeat, updates window and events
		app.Update();
	}

	std::cout << "Closing window...\n";
}
