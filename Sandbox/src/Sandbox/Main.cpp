//Welcome to LFW(THE LUNA FRAMEWORK)!
/*
	@author Joacim Lord (c) 2020-2022.
	<This project was last edited 220827>
*/

//Contains everything you need!
#include "LFW.h"

//Needed if you want to build your own UI.
#include <imgui/imgui.h>

void LFW::Application::BuildUI()
{
	//Basic example to show the framerate of your application
	ImGui::Begin("My own UI!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	//Builds the debug panel
	LFW::Debug::BuildLogWindow();
}


int main()
{
	//LFW::DebugGUI::Init(true);
	//LFW::Docking::Init(true);
	LFW::Application app("App");

	//-------------------------------------------------------
	//EXAMPLE - How to load and set up a sprite with a texture and color!
	//-------------------------------------------------------
	
	//Add your own filepath, the example is placeholder!
	LFW::Sprite texturedSprite;
	texturedSprite.filePath = "path_to_texture";
	texturedSprite.pixelated = false;
	texturedSprite.SetTexture(texturedSprite.filePath);
	texturedSprite.SetSize(0.5f, 0.3f);
	texturedSprite.SetPosition(-0.5f, 0.0f);

	LFW::Sprite orangeSprite;
	orangeSprite.color = LFW::Colors::orange;
	orangeSprite.SetSize(0.5f, 0.3f);
	orangeSprite.SetPosition(0.5f, 0.0f);


	//-------------------------------------------------------
	//EXAMPLE - Spritesheet usage
	//-------------------------------------------------------
	//Init the spritesheet
	LFW::Spritesheet spriteSheet;

	//Create the 2D quads from the spritesheet with the SpriteSheetManager. 
	//Set spritesheet width & height, sprite width & height,
	//number of sprites and if there is any spacing between the sprites(in pixels)
	LFW::SpritesheetManager::CreateSpritesheet(spriteSheet, 40, 40, 5, 5, 5, 0);

	//Load the spritesheet with the SpriteSheetManager. Takes in the spritesheet, filepath and if the sprites needs pixelation (for pixel art)
	LFW::SpritesheetManager::LoadSpritesheet(spriteSheet, "path_to_spritesheet", true);


	//Init the sprites to set their size & positions
	LFW::Sprite sprite;
	sprite.SetSize(0.3f, 0.3f);
	sprite.SetPosition(-0.5f, 0.0f);

	spriteSheet.AddSprite(sprite);

	//-------------------------------------------------------
	//EXAMPLE - How to use the Audio Engine
	//-------------------------------------------------------

	//const char* soundFilePath = "";
	//LFW::AudioEngine audioEngine;
	//audioEngine.PlayAudioFromFile(soundFilePath);


	//For calculating frame time
	float lastFrameTime = 0.0f;

	//Main-loop
	while (app.IsRunning())
	{
		//Calculate delta
		float elapsedTime = app.GetElapsedRuntime();
		LFW::DeltaTime deltaTime = elapsedTime - lastFrameTime;
		lastFrameTime = elapsedTime;

		app.Clear(LFW::Colors::grey);

		// Example of how to use ScreenToWorldPoint()
		if (LFW::Input::IsMouseButtonPressed(LFW::Mouse::Button0))
		{
			glm::vec2 mousePos = app.ScreenToWorldPoint();
			spriteSheet.GetSprite(0).SetPosition(mousePos.x, mousePos.y);
		}

		//Draw from the spritesheet
		app.Render(spriteSheet);

		app.Render(texturedSprite);
		app.Render(orangeSprite);

		app.Display();
	}
}