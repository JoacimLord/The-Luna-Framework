//Welcome to LFW(THE LUNA FRAMEWORK)!
/*
	@author Joacim Lord.
	<This project was last edited 220816>
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
	LFW::Viewport::Init(true);
	LFW::Application app("App");

	//Example of how to load and set up a sprite with a texture and color! (Documentation will come later on)
	//Add your own filepath, the example is placeholder!
	LFW::Sprite texturedSprite;
	texturedSprite.filePath = "your_filepath_here_with_image_extension(.jpg, .png)";
	texturedSprite.pixelated = false;
	texturedSprite.SetTexture(texturedSprite.filePath);
	texturedSprite.SetSize(0.5f, 0.3f);
	texturedSprite.SetPosition(-0.5f, 0.0f);

	LFW::Sprite orangeSprite;
	orangeSprite.color = LFW::Colors::Orange;
	orangeSprite.SetSize(0.5f, 0.3f);
	orangeSprite.SetPosition(0.5f, 0.0f);

	//Example of the Audio Engine
	const char* soundFilePath = "";
	LFW::AudioEngine audioEngine;
	audioEngine.PlayAudioFromFile(soundFilePath);


	//For calculating frame time
	float lastFrameTime = 0.0f;

	//Main-loop
	while (app.IsRunning())
	{
		//Calculate delta
		float elapsedTime = app.GetElapsedRuntime();
		LFW::DeltaTime deltaTime = elapsedTime - lastFrameTime;
		lastFrameTime = elapsedTime;

		app.Clear(LFW::Colors::Grey);

		app.Render(texturedSprite);
		app.Render(orangeSprite);

		app.Display();
	}
}