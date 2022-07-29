# LFW (The Luna Framework) - Version 1.05.00

LFW is a low level framework based on the API of my 3D game engine "Luna" (currently in development).

The intention of this framework is to build any kind of GUI app, but it's probably most suitable for simple 2D games at this stage.
It currently only support development on Windows with Visual Studio Community 2019.


The framework has full 2D support but misses audio and font rendering, this is currently being worked on and will be added in the near future.
The API is heavily based on the syntax of the library SFML with a similar setup for your main loop and rendering (examples of how you get started is in the Main.cpp file in the Sandbox project).


Third party libraries in use:

- Glad
- Dear ImGui
- GLFW
- glm
- stb_image



# How to get started

Simply clone, fork or download the project. Run the Setup.bat file to generate your solution.
The only file that you need to include is the "LFW.h" header file and the <imgui/imgui.h> file.
Feel free to to rename and use the Sandbox project as your starting point.




# - API DOCUMENTATION

## Modules

 ### - Simple LFW Example
 ### - Viewport
 ### - Application functionality
 ### - DeltaTime
 ### - Sprites
 ### - Input
 ### - Camera
 ### - Math Library
 ### - Debug Panel
 ### - Application window functionality




# Simple LFW Example
 A simple example of a bare bones application. This is included in the Sandbox/src/Main.cpp file.

```cpp
#include "LFW.h"
#include <imgui/imgui.h>

//This needs to be included. If you don't want to use ImGui this can be left blank but still needs to be here!
void LFW::Application::BuildUI()
{
}

int main()
{
	//How to initalize a window and name it.
	LFW::Application app("App"); 

	while (app.IsRunning())
	{
		/* Disclaimer */
		//This functionality has to happen in this specific order:
		// 1. Clear()
		// 2. Render(single_sprite)
		// 3. Display()
		// Logic should happen before the Render() function (for example Input, collision etc)

		//The clear function can be called empty (Clear()) to get a black color as default.
		//It can also be called with values (Clear(1.0f, 1.0f, 1.0f, 1.0f)) or as in this example, with LFW::Colors!
		app.Clear(LFW::Colors::Grey);

		app.Render();

		app.Display(); 
	}
}
```


# Viewport

The LFW framework renders to a Dear ImGui panel by default called "Viewport". This is done by rendering a texture of the screenspace into an image and displaying it in the panel.
The Viewport also brings the ability to freely move and dock your own panels anywhere inside the application.

This is a feature commonly used by standard applications but maybe not so much for games. Therefore it's possible to disable the feature and just render a "normal" GLFW window.
To disable the ImGui viewport, simply call "LFW::Viewport::Init(false);" before you initialize the application.

Initializing the viewport to true if you want to use any Dear ImGui feature (build your own panels, the Debug Console Panel, etc).


Example:
```cpp
#include "LFW.h"
#include <imgui/imgui.h>

//This needs to be included. If you don't want to use ImGui this can be left blank but still needs to be here!
void LFW::Application::BuildUI()
{
}

int main()
{
	//This sets the viewport to not be initialized. Use true to init the viewport (and Dear ImGui).
	LFW::Viewport::Init(false);
	LFW::Application app("App"); 

	while (app.IsRunning())
	{
		app.Clear(1.0f, 0.0f, 1.0f, 1.0f);
		app.Render();
		app.Display(); 
	}
}
```


# Application Functionality

The application comes with some basic GLFW features that you come to expect.
This includes:

- SetTitle(std::string new_app_title)
- SetIcon(std::string path_to_icon)

- WIP! (Not ready for usage) SetDefaultIcon()
- WIP! (Not ready for usage) SetCustomCursor()
- WIP! (Not ready for usage) SetDefaultCursor()

- SetWindowConstraint(float minWidth, float minHeight, float maxWidth, float maxHeight)
- SetWindowMinSize(float minWidth, float minHeight)
- SetWindowMaxSize(float maxWidth, float maxHeight)

- SetMouseCursorVisibility(bool true/false)

Use this funcionality after initializing the application.

```cpp
int main()
{
	//This sets the viewport to not be initialized. Use true to init the viewport (and Dear ImGui).
	LFW::Application app("App"); 
	app.SetTitle("Hello World");

	std::string icon_file_path = "path.png";
	app.SetIcon(icon_file_path);
}
```



# DeltaTime
DeltaTime is calculated to make your sprites and logic happen with frametime in consideration.
```cpp
int main()
{
	//How to initalize a window and name it.
	LFW::Application app("App"); 

	//For calculating frame time
	float lastFrameTime = 0.0f;
	while (app.IsRunning())
	{
		//Calculate delta
		float elapsedTime = app.GetElapsedRuntime();
		LFW::DeltaTime deltaTime = elapsedTime - lastFrameTime;
		lastFrameTime = elapsedTime;

		app.Clear(1.0f, 0.0f, 1.0f, 1.0f);
		app.Render();
		app.Display(); 
	}
}
```



# Sprites

Initialize your sprites from the LFW namespace before the main loop of your application.
```cpp

LFW::Sprite texturedSprite;
texturedSprite.filePath = "your_filepath_here_with_image_extension(.jpg, .png)";
texturedSprite.SetTexture(texturedSprite.filePath);
texturedSprite.SetSize(0.5f, 0.3f);
texturedSprite.SetPosition(-0.5f, 0.0f);

LFW::Sprite orangeSprite;
orangeSprite.color = LFW::Colors::Orange;
orangeSprite.SetSize(0.5f, 0.3f);
orangeSprite.SetPosition(0.5f, 0.0f);
```

The sprite size is in 1:1 units from the cameras perspective and not in pixels.

Sprite functionality:
- SetTexture()
- color (takes in a glm::vec4 value)
- SetPosition(x, y)
- SetSize(x, y)
- .filePath (to load the texture)
- SetRotation(X, Y, Z)

Sprites use "anchors" to manipulate it's orientation in the 2D world. Anchors are just transforms that control position, size and rotation.

This is needed for textures to know the location for their placement. Use it to place objects in your 2d scene.
Remember to render the objects in the correct order as you want to display them.

## Textures or color
Sprites can load in a texture or a color defined by "spriteName.color = value;"
If a texture filepath is defined, the sprite will always load the texture.
If no filepath is defined the sprite uses the colorvalue (0 by default).
Pre-defined colors can be found in the "LFW::Colors" namespace but you can also define your own with glm::vec4s.

Make sure to have either the texture or color defined before rendering your sprite!



# Input (keyboard & mouse)

Use "LFW::Input" in runtime to trigger keypressed or mousepressed events. Mainly used to move around your sprites in realtime!

Example:
```cpp
if (LFW::Input::IsKeyPressed(LFW::Key::TheKeyYouWant))
{
	//Do something
}

if (LFW::Input::IsMouseButtonPressed(LFW::Mouse::TheMouseButtonYouWant))
{
	//Do something 
}
```



Example of moving around a sprite using LFW::DeltaTime and the sprites LFW::Anchor:
```cpp
int main()
{
	//How to initalize a window and name it.
	LFW::Application app("App"); 
	//Init a sprite before the while loop of your application and set it's color, size and position
	LFW::Sprite orangeSprite;
	orangeSprite.color = LFW::Colors::Orange;
	orangeSprite.SetSize(0.5f, 0.3f);
	orangeSprite.SetPosition(0.5f, 0.0f);

	//For calculating frame time
	float lastFrameTime = 0.0f;

	//Variable to store the speed of which the sprite should move
	float playerSpeed = 1.0f;

	while (app.IsRunning())
	{
		//Calculate delta
		float elapsedTime = app.GetElapsedRuntime();
		LFW::DeltaTime deltaTime = elapsedTime - lastFrameTime;
		lastFrameTime = elapsedTime;

		app.Clear(1.0f, 0.0f, 1.0f, 1.0f);
		
		///W key for moving up
		if (LFW::Input::IsKeyPressed(LFW::Key::W))
		{
			orangeSprite.anchor.Translation.y += playerSpeed * deltaTime;
		}

		//S key for moving down
		else if (LFW::Input::IsKeyPressed(LFW::Key::S))
		{
			orangeSprite.anchor.Translation.y -= playerSpeed * deltaTime;
		}

		//A key for moving left
		if (LFW::Input::IsKeyPressed(LFW::Key::A))
		{
			orangeSprite.anchor.Translation.x -= playerSpeed * deltaTime;
		}

		//D key for moving right
		else if (LFW::Input::IsKeyPressed(LFW::Key::D))
		{
			orangeSprite.anchor.Translation.x += playerSpeed * deltaTime;
		}


		app.Render(orangeSprite);
		app.Display(); 
	}
}
```


# Camera (Controls & 'Follow')

The application always renderers the sprites using a basic orthographic camera (flat for 2D).
The camera can be controlled with the Arrow-keys (customizable keys will come later on).
It's also possible to set the camera to follow a specific Transform (Anchor). A little confusing but it's the same thing!

```cpp

	//Enables controls for the camera. Current control scheme: Arrow-keys.
	//This function needs to have the DeltaTime variable passed in.
	//The option of a camera that can be controlled without DeltaTime is in progress.
	app.CheckInputForCamera(deltaTime);

	//Sets the cameras position follow a specific anchor point.
	app.SetCameraToFollowTransform(orangeSprite.anchor);

```


# Math Library

LFWs own implementation of vectors. This is heavily WIP and I recommend to just use the glm library for vectors.
These structs can be initialized with and without constructor arguments to set length.
```cpp

	//How to use LFW::Vectors
	LFW::Vec2 vec2;
	LFW::Vec3 vec3;
	LFW::Vec3 vec4;
```

Small Math library inmplemented in LFW for mathematical operations.
```cpp

	//How to use LFW::Mathf
	LFW::Mathf::Floor(x, y);
	LFW::Mathf::Clamp(x, y);
	LFW::Mathf::PI();
	LFW::Mathf::Sqrt(x);
	LFW::Mathf::Max(x, y);
	LFW::Mathf::Min(x, y);	
```

Current Math Lib Functionality

	Floor() -- Returns the largest integer smaller than or equal to (f)
	Clamp() -- Returns the given value between those numbers. Example: 1 & 3 return 2.
	PI() ----- Returns the PI number with 7,9 or 11 floating number.
	Sqrt() --- Returns the sqrt of argument value (support for int, float & double).  Wrapper around std::sqrt().
	Max() ---- Returns the largest of two values
	Min() ---- Returns the smallest of two values


Mathf Testcases

	//SQRT()
	std::cout << "Sqrt of 9: " << LFW::MathF::Sqrt(9) << "\n";

	//MAX()
	std::cout << "Biggest value of 10 and 5: " << LFW::MathF::Max(5.0f, 10.0f) << "\n";
	std::cout << "Biggest value of 30 and 1: " << LFW::MathF::Max(30.0f, 1.0f) << "\n";
	std::cout << "Biggest value of 14 and 14: " << LFW::MathF::Max(14.0f, 14.0f) << "\n";
	
	//MIN()
	std::cout << "Smallest value of 10 and 5: " << LFW::MathF::Min(5.0f, 10.0f) << "\n";
	std::cout << "Smallest value of 30 and 1: " << LFW::MathF::Min(30.0f, 1.0f) << "\n";
	std::cout << "Smallest value of 14 and 14: " << LFW::MathF::Min(14.0f, 14.0f) << "\n";
	
	// CLAMP()
	LFW::MathF::Clamp(0,5);    //Prints 5
	LFW::MathF::Clamp(3, 5);   //Prints 2
	LFW::MathF::Clamp(-2, 12); //Prints 14
	LFW::MathF::Clamp(-5,5);   //Prints 10
	
	//FLOOR()
	LFW::MathF::Floor(10.0f);  //Prints 10
	LFW::MathF::Floor(10.2f);  //Prints 10
	LFW::MathF::Floor(10.7f);  //Prints 10
	LFW::MathF::Floor(-10.0f); //Prints -10
	LFW::MathF::Floor(-10.2f); //Prints -10
	LFW::MathF::Floor(-10.7f); //Prints -11
	LFW::MathF::Floor(-20.9f); //Prints -21
	LFW::MathF::Floor(-13.6f); //Prints -14
	LFW::MathF::Floor(10.7f);	 //Prints 10




# "Debug" namespace

The Debug namespace contains my own version of a Dear ImGui panel that functions as a Console Log Window.
To build the Debug Log Panel the Viewport needs to be initialized, <imgui> included in your Main file and the LFW::Application::BuildUI() added to your file.

```cpp
	//Build your own UI here by declairing this function!
	void LFW::Application::BuildUI()
	{
		Debug::BuildLogWindow();
	}

```

Add a Debug::Log(msg, int) in your Main.cpp to choose a specific color.
0 - Green
1 - Yellow
2 - Orange
3 - Red
(Or just a default message (white text)).

```cpp
	//Debug examples
	Debug::Log("Msg_WhiteColor");
	Debug::Log("Msg_GreenColor", 0);
	Debug::Log("Msg_YellowColor", 1);
	Debug::Log("Msg_OrangeColor", 2);
	Debug::Log("Msg_RedColor", 3);
```

This can also be used in runtime like the example below

```cpp
	//Example of Debug:Log() in runtime
	if (LFW::Input::IsKeyPressed(LFW::Key::Space)) Debug::Log("Spacebar was pressed!");
```



# Disclaimer

I don't recommend to use any other API calls than the ones reachable from the Application class.
This repo and documentation is heavily in progress and will be frequently changed!

Features soon to come:
- Audio
- Font rendering


Thanks for using my framework in your own project <3