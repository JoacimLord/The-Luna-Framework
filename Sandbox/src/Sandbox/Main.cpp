//"THE LUNA FRAMEWORK" (LFW) - Last edited 220715

#include "LFW.h"		 //Contains everything you need!
#include <imgui/imgui.h> //Needed if you want to build your own UI.


//Build your own UI here by declairing this function!
void LFW::Application::BuildUI()
{
	static float clrEdit4[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
	//Comment out / remove to not use ImGui
	ImGui::Begin("My own UI!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::ColorEdit4("Color", clrEdit4); //This is for the demo. Possible to use glm::value_ptr() instead and point to the actual variable.
	ImGui::End();
	LFW::Debug::BuildLogWindow();
}


int main()
{
	std::cout << "Opening new window!\n"; //Console log
	LFW::Application app("App");

	//Example of how to load and set up a sprite with a texture and color! (Documentation will come later on)
	//Add your own filepath, the example is placeholder!
	LFW::Sprite texturedSprite;
	texturedSprite.filePath = "your_filepath_here_with_image_extension(.jpg, .png)";
	texturedSprite.SetTexture(texturedSprite.filePath);
	texturedSprite.SetSize(0.5f, 0.3f);
	texturedSprite.SetPosition(0.0f, 0.0f);

	LFW::Sprite orangeSprite;
	orangeSprite.color = LFW::Colors::Orange;
	orangeSprite.SetSize(0.5f, 0.3f);
	orangeSprite.SetPosition(0.5f, 0.5f);


	//Un-comment to show GUI examples (ImGui).
	//app.ShowImGuiDemoWindow();

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

		//Debug examples
		if (LFW::Input::IsKeyPressed(LFW::Key::Space))
		{
			LFW::Debug::Log("Msg_WhiteColor");
			LFW::Debug::Log("Msg_GreenColor", 0);
			LFW::Debug::Log("Msg_YellowColor", 1);
			LFW::Debug::Log("Msg_OrangeColor", 2);
			LFW::Debug::Log("Msg_RedColor", 3);
		}

		app.Render(texturedSprite);
		app.Render(orangeSprite);

		app.Display();
	}
	std::cout << "Closing window...\n";
}