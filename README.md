# The Luna Framework(LFW) - Version 1.03

Last update:
- Added a WIP implementation of a scene camera with some basic behaviours. Example in <Main.cpp> and below in 'API DOC'. (220612)
- Added basic support for multiple shaders. Now possible to render textures and simple shader colors at the same time.   (220608)

(last edited 220615)



"The Luna Framework"(LFW) is a low level framework based on the API of the game engine "Luna" (currently in development).

The intention of this framework is to build any kind of GUI app, but it's probably most suitable for simple 2D games for now.
It only supports 2D graphics and GUI, audio wil also be added in the near future.

The API is heavily based on the syntax of the library SFML with a similar setup for your main loop and rendering (examples of how you get started is in the Main.cpp file in the Sandbox project).
The framework always renders graphics to a framebuffer that displays it in a ImGui window called "Viewport". Therefore, we need to #include <imgui/imgui.h> in our main file.


If you don't want to use opengl for graphics and only intends to create a "ImGui-only" app, feel free to just use the ImGui-Viewport as your main window. 
Support to turn off the viewport will come in a later update.


Third party libraries in use:

- Glad
- Dear ImGui
- GLFW
- glm
- stb_image



# How to get started

Simply clone, fork or download the project. Run the Setup.bat file to generate your solution.
The only file that you need to include is the "Luna.h" header file and the <imgui/imgui.h> file.
Feel free to use the Sandbox project as your starting point.

The framework currently only supports development for Windows.



# - API DOC -


 A simple example of a bare bones application

```cpp
//This includes the whole framework
#include "LFW.h"

//This needs to be included
#include <imgui/imgui.h>

//This needs to be included. If you don't want to use ImGui this can be left blank but still needs to be here!
//Check out the ImGui repo for API documentation!
void Luna::Application::BuildUI()
{
}

int main()
{
	//How to initalize a window and name it. Recommended to use a smart ptr, this stack allocation is for demo purposes.
	Luna::Application app("App"); 

	//Move directly into the while-loop, app.IsRunning() needs to be included here
	while (app.IsRunning())
	{
		//These two are for rendering opengl in the viewport (graphics)
		app.Clear(1.0f, 0.0f, 1.0f, 1.0f); //Initializes the viewport as a rendering texture

		app.Render(); //To render graphics to the viewport, needs to take in a texture OR a color (vec4), and a GetTransform() from the Anchor class.

		//If your application only need the ImGui setup, only keep this */
		app.Display(); 
	}
}

```

As you can see in the example we render to the window with a texture and an 'anchor'.
The texture needs to be a pointer.

An anchor is just a transform with a scale, translation and rotation combined.
Initiate like:

```cpp

Luna::Anchor anchor;

```

From here you can control 3 attributes of the anchor:
- Translation (position)
- Size
- Rotation (currently not working, will be fixed later)

Anchors is needed for textures to know the location for their placement. Use it to place objects in your 2d scene.
Remember to render the objects in the correct order as you want to display them.

For example if you're rendering game objects:

1. Background
2. Props that is walkable
3. Player
4. Enemies
5. Trees that's supposed to cover the characters

etc...


# ANCHOR & TEXTURE EXAMPLE

Full example of rendering a texture to an anchor point on the screen:

```cpp
#include "LFW.h"

//This is to make it more clear and to "bind it" to an object.
struct ExampleObject
{
	Luna::Anchor anchor; //Here we instantiate it

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

//Example UI, shows the framerate of the app!
void Luna::Application::BuildUI()
{
	ImGui::Begin("My own UI!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}

int main()
{
	//How to initalize a window and name it
	Luna::Application app("App"); 

	//Texture loaded as a shared ptr. filepath represents the filepath to whichever folder you store your assets in.
	std::shared_ptr<Luna::Texture> texture = std::make_shared<Luna::Texture>(filepath);

	//Initiate the object and set it's size (width, height) and location (x, y)
	ExampleObject object;
	object.SetSize(50.0f, 50.0f);
	object.SetPosition(600.0f, 350.0f);

	//Move directly into the while-loop, app.IsRunning() needs to be included here as it's directly linked with a "close the window via the exit button" event
	while (app.IsRunning())
	{
		//Logic here, before we render

		//Example of using the LunaAPI to take input from a keyboard and translate (move) the object by manipulating it's anchor point.
		if (Luna::Input::IsKeyPressed(Luna::Key::Z))
		{
			object.anchor.Translation.x += 10.0f;
		}

		//Clear the screen and set up the framebuffer, needs to happen every frame
		app.Clear(1.0f, 0.0f, 1.0f, 1.0f);

		//Then we render textures in the correct order (furthest "back" to the "front" as in the example list above)
		app.Render(texture, object.anchor.GetTransform()); //Renders the texture at the anchors position and with the anchors scale.
		
		//Display our graphics
		app.Display();
	}
}

```

# DeltaTime

```cpp

//This is how you calculate deltatime with the API
float elapsedTime = app.GetElapsedRuntime();
Luna::DeltaTime deltaTime = elapsedTime - lastFrameTime;
lastFrameTime = elapsedTime;


```

# Input (keyboard & mouse)

```cpp

if (Luna::Input::IsKeyPressed(Luna::Key::X))
{
	//Do something
}

if (Luna::Input::IsMouseButtonPressed(Luna::Mouse::ButtonLeft))
{
	//Do something 
}

```

# Camera (Controls & 'Follow')

These functions will be changed and moved to a seperate CameraController class (or something like that :)), this is heavy WIP and currently only for demo purposes!
```cpp

	//Enables controls for the camera. Current control scheme: LeftShift + Arrows
	app.CheckInputForCamera();

	//Sets the cameras position to be the same as the passed in vec3 (for example the Anchors 'Translation')
	app.SetCameraToFollowTransform(demoObject.anchor.Translation);

```


# Disclaimer

I don't recommend to use any other API calls than the ones reachable from the Application class.

# Remember to always

0. Don't forget to include the correct files and the imgui-function (and leave it blank if you don't want it)!
1. Instantiate the window with a title
2. Instantiate other objects and then use a while-loop that checks IsRunning()
3. Game logic goes here (for example input and such that needs to be checked every fram)!
4. Clear the window and prepare the framebuffer
5. Render your graphics
6. Display



Thanks for using my framework in your own project <3