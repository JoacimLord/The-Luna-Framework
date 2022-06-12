
//THE LUNA FRAMEWORK ('TLFW') - Author Note (220612)
/*
	Parts of this projects base API layout has taken inspiration from The Chernos "Game Engine" series. Thank you!
*/

#include "Luna.h"		 //Contains everything you need!
#include <imgui/imgui.h> //Needed if you want to build your own UI.

struct Entity
{
	Luna::Anchor anchor; // This a matrix with position, scale and rotation.
	//This is what you use and manipulate if you want to (for example) move a texture around.

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
	ImGui::ColorEdit4("Color", clrEdit4); //This is for the demo. Possible to use glm::value_ptr() instead and point to the actual variable.
	ImGui::End();
}

//Demo for setting the color from the ImGui ColorEdit4!
glm::vec4 BindColorFromValues(static float clrIn[4])
{
	glm::vec4 clr;
	clr[0] = clrIn[0];
	clr[1] = clrIn[1];
	clr[2] = clrIn[2];
	clr[3] = 1.0f; //Transparency

	return clr;
}

//Basic input
void CheckInputForMovingEntitiesInScene(Entity& entity, float speed, Luna::DeltaTime deltaTime)
{
	if (Luna::Input::IsKeyPressed(Luna::Key::W))
	{
		entity.anchor.Translation.y += speed * deltaTime;
	}
	else if (Luna::Input::IsKeyPressed(Luna::Key::S))
	{
		entity.anchor.Translation.y -= speed * deltaTime;
	}
	if (Luna::Input::IsKeyPressed(Luna::Key::A))
	{
		entity.anchor.Translation.x -= speed * deltaTime;
	}
	else if (Luna::Input::IsKeyPressed(Luna::Key::D))
	{
		entity.anchor.Translation.x += speed * deltaTime;
	}
}


//Here we go!
int main()
{
	std::cout << "Opening new window!\n"; //Console log
	Luna::Application app("App"); //Recommended to use a smart ptr instead!

	//Object with attached transform
	Entity demoObject;
	demoObject.SetSize(0.5f, 0.3f); //In meters, not pixels
	demoObject.SetPosition(0.0f, 0.0f);

	//"Loose" transform
	Luna::Anchor demoPosition;
	demoPosition.Translation.x = 0.5f;
	demoPosition.Translation.y = 0.5f;
	demoPosition.Scale.x = 0.5f;
	demoPosition.Scale.y = 0.3f;

	//For calculating frame time
	float lastFrameTime = 0.0f;

	//Un-comment to show GUI examples (ImGui).
	//app.ShowImGuiDemoWindow();

	const char* filePath = "Resources/red.png";
	std::shared_ptr<Luna::Texture> texture = std::make_shared<Luna::Texture>(filePath);

	float demoObjectMovementSpeed = 1.0f;

	//Main-loop
	while (app.IsRunning())
	{
		//Calculate delta
		float elapsedTime = app.GetElapsedRuntime();
		Luna::DeltaTime deltaTime = elapsedTime - lastFrameTime;
		lastFrameTime = elapsedTime;

		//Clears screen with pre-defined color from the Colors lib or with a vec4 value (last one is the transparency)
		app.Clear(Luna::Colors::Grey);

		app.CheckInputForCamera();
		CheckInputForMovingEntitiesInScene(demoObject, demoObjectMovementSpeed, deltaTime);

		//Create a color that takes on the value from the ImGui ColorEdit4. Attaches the color to the shader color
		glm::vec4 color = BindColorFromValues(clrEdit4);
		app.Render(texture, demoObject.anchor.GetTransform());		//Renders texture on entities transform
		app.RenderShaderColor(color, demoPosition.GetTransform());  //Renders flat color on demoPosition

		//Clears the framebuffer. Flush and repeat, updates window and events
		app.Display();
	}
	std::cout << "Closing window...\n";
}