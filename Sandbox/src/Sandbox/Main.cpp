//Welcome to LFW(THE LUNA FRAMEWORK)!
/*
	@author Joacim Lord (c) 2020-2022.
	<This project was last edited 220909>
*/

//Contains everything you need!
#include "LFW.h"

//Needed if you want to build your own UI.
#include <imgui/imgui.h>

void LFW::Application::BuildUI()
{
	////Basic example to show the framerate of your application
	//ImGui::Begin("My own UI!");
	//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//ImGui::End();
	//
	////Builds the debug panel
	//LFW::Debug::BuildLogWindow();
}

int main()
{
	//Init the application with a title
	LFW::Application app("App");

	//Setup of a sprite with a color
	LFW::Sprite orangeSprite;
	orangeSprite.color = LFW::Colors::orange;
	orangeSprite.SetSize(0.5f, 0.3f);
	orangeSprite.SetPosition(0.5f, 0.0f);

	//Main-loop
	while (app.IsRunning())
	{
		//Get DeltaTime from Application
		LFW::DeltaTime deltaTime = app.GetDeltaTime();

		//Clears screen
		app.Clear(LFW::Colors::grey);

		//Draw a single sprite with a pre-defined color
		app.Render(orangeSprite);

		//Displays gfx to screen
		app.Display();
	}
}