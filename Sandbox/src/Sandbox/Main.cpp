//"THE LUNA FRAMEWORK" (LFW)

#include "LFW.h"		 //Contains everything you need!
#include <imgui/imgui.h> //Needed if you want to build your own UI.

struct Entity
{
	LFW::Anchor anchor; // This a matrix with position, scale and rotation.
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


static float clrEdit4[4] = { 0.4f, 0.7f, 0.0f, 0.5f };

//Build your own UI here by declairing this function!
void LFW::Application::BuildUI()
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
void CheckInputForMovingEntitiesInScene(Entity& entity, float speed, LFW::DeltaTime deltaTime)
{
	if (LFW::Input::IsKeyPressed(LFW::Key::W))
	{
		entity.anchor.Translation.y += speed * deltaTime;
	}
	else if (LFW::Input::IsKeyPressed(LFW::Key::S))
	{
		entity.anchor.Translation.y -= speed * deltaTime;
	}
	if (LFW::Input::IsKeyPressed(LFW::Key::A))
	{
		entity.anchor.Translation.x -= speed * deltaTime;
	}
	else if (LFW::Input::IsKeyPressed(LFW::Key::D))
	{
		entity.anchor.Translation.x += speed * deltaTime;
	}
}

int main()
{
	std::cout << "Opening new window!\n"; //Console log
	LFW::Application app("App");

	//Object with attached transform
	Entity demoObject;
	demoObject.SetSize(0.5f, 0.3f); //In meters, not pixels
	demoObject.SetPosition(0.0f, 0.0f);

	//"Loose" transform
	LFW::Anchor demoPosition;
	demoPosition.Translation.x = 0.5f;
	demoPosition.Translation.y = 0.5f;
	demoPosition.Scale.x = 0.5f;
	demoPosition.Scale.y = 0.3f;


	//For calculating frame time
	float lastFrameTime = 0.0f;

	//Un-comment to show GUI examples (ImGui).
	//app.ShowImGuiDemoWindow();

	const char* filePath = "Resources/red.png";
	std::shared_ptr<LFW::Texture> texture = std::make_shared<LFW::Texture>(filePath);

	float demoObjectMovementSpeed = 1.0f;

	//Main-loop
	while (app.IsRunning())
	{
		//Calculate delta
		float elapsedTime = app.GetElapsedRuntime();
		LFW::DeltaTime deltaTime = elapsedTime - lastFrameTime;
		lastFrameTime = elapsedTime;

		//Clears screen with pre-defined color from the Colors lib or with a vec4 value (last one is the transparency)
		app.Clear(LFW::Colors::Grey);


		//--------------------------------------------------------------
		//Camera behaviours! These can't be used at the same time. WIP
		//--------------------------------------------------------------
		
		//app.CheckInputForCamera(); //Moves camera for 'editor operations'
		app.SetCameraToFollowTransform(demoObject.anchor.Translation); //Sets the camera to follow a specific transform (for example a player)

		CheckInputForMovingEntitiesInScene(demoObject, demoObjectMovementSpeed, deltaTime);

		//Create a color that takes on the value from the ImGui ColorEdit4. Attaches the color to the shader color
		glm::vec4 color = BindColorFromValues(clrEdit4);
		app.Render(texture, demoObject.anchor.GetTransform());		//Renders texture on entities transform
		app.Render(color, demoPosition.GetTransform());  //Renders flat color on demoPosition

		//Clears the framebuffer. Flush and repeat, updates window and events
		app.Display();
	}
	std::cout << "Closing window...\n";
}