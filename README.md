# LFW (The Luna Framework) - Version 1.10.02

LFW is a low level framework based on the API of my 3D game engine "Luna" (currently in development).

The intention of this framework is to build any kind of GUI app, but it's probably most suitable for simple 2D games at this stage.
It currently only support development on Windows with Visual Studio Community 2019 (this can be fixed by editing the Setup file).


Third party libraries in use:

- Glad
- Dear ImGui
- GLFW
- glm
- stb_image
- miniaudio



# How to get started

Clone, fork or download the project, and run the Setup/Setup.bat file to generate your solution.
The only file that you need to include is the "LFW.h" header file and the <imgui/imgui.h> file.
I suggest to rename the Sandbox project and use that as your starting point!



# - API DOCUMENTATION -

## Modules

 ### - Simple LFW Example
 ### - Debug GUI & Docking
 ### - Application functionality
 ### - DeltaTime
 ### - Sprites
 ### - Spritesheets
 ### - Input (keyboard & mouse)
 ### - Mouse Position
 ### - Camera
 ### - Math Library
 ### - Debug Panel
 ### - Application window functionality
 ### - AudioEngine
 ### - Features Soon To Come
 ### - Disclaimer



# Simple LFW Example
 A simple example of a "bare bones" application. This is included in the Sandbox/src/Main.cpp file.

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



# Debug GUI & Docking

LFW uses Dear ImGui to make it easy to integrate debugging/GUI panels inside your application.

There is 3 different options on how to use Dear ImGui in LFW.
1. Docking (used for multimedia apps).
2. DebugGUI (used mostly to debug games).
3. Disable Dear ImGui in general.

Docking makes it possible to freely move around your panels and dock them where you feel like to. This also moves the rendering to be displayed in a ImGui Panel called "Viewport" that can be docked anywhere.
DebugGUI enables "floating" panels that can't be docked, but can be moved around. This can be useful for debugging games. This renders to the GLFW window and not into a Dear ImGui panel.
If none of these options is enabled, LFW renders directly to the GLFW window.

To create custom Dear ImGui panels, initialize them in the BuilUI function that LFW provides with the Dear ImGui API (documentation can be found in their repo on GitHub).


DISCLAIMERS
1. Docking and DebugGUI CAN NOT be used together! Use ONE of these or none.
2. This needs to happen BEFORE initalizing the application (as in the example).
3. If you decide to use the Docking-feature, the function for converting ScreenToWorldPoint is not working properly since it gets calculated depending on the GLFW window, and screen resizing does not consider the framebuffer rendering to the Dear ImGui window (which can lead to strange "streches" in sprites if not set to the correct aspectratio). This issue is currently being worked on.
4. Both of these are initalized as false by default. If you don't want to use any of it, just initalize the application as normal.
5. Even if this isn't used in your application, both the #include <imgui/imgui.h> and void LFW::Application::BuildUI() has to be defined inside the Main.cpp file (but can of course be left empty).

Example - Docking:
```cpp
#include "LFW.h"
#include <imgui/imgui.h>

//This needs to be included. If you don't want to use ImGui this can be left blank but still needs to be here!
void LFW::Application::BuildUI()
{
}

int main()
{
	//This sets the viewport (Dear ImGui panel) to be initialized and enables docking.
	LFW::Docking::Init(true);

	LFW::Application app("App"); 

	while (app.IsRunning())
	{
		app.Clear(1.0f, 0.0f, 1.0f, 1.0f);
		app.Render();
		app.Display(); 
	}
}
```

Example - Debug GUI:
```cpp
#include "LFW.h"
#include <imgui/imgui.h>

//This needs to be included. If you don't want to use ImGui this can be left blank but still needs to be here!
void LFW::Application::BuildUI()
{
}

int main()
{
	//This enables Dear ImGui panels but keeps rendering to the GLFW window (which has correct resizing and ScreenToWorld convertion).
	LFW::DebugGUI::Init(true);

	LFW::Application app("App"); 

	while (app.IsRunning())
	{
		app.Clear(1.0f, 0.0f, 1.0f, 1.0f);
		app.Render();
		app.Display(); 
	}
}
```

Example - Disabled Dear ImGui:
```cpp
#include "LFW.h"
#include <imgui/imgui.h>

//This needs to be included. If you don't want to use ImGui this can be left blank but still needs to be here!
void LFW::Application::BuildUI()
{
}

int main()
{
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
DeltaTime is calculated to make your sprites and logic update with frametime in consideration.
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

In this example we render each sprite individually. This means that they have to be in separate files (.jpg, .png).
To render sprites from a spritesheet, see the "Spritesheet" section.

Initialize your sprites from the LFW namespace before the main loop of your application.
```cpp

LFW::Sprite texturedSprite;
texturedSprite.filePath = "your_filepath_here_with_image_extension(.jpg, .png)";
texturedSprite.pixelation = false;
texturedSprite.SetTexture(texturedSprite.filePath);
texturedSprite.SetSize(0.5f, 0.3f);
texturedSprite.SetPosition(-0.5f, 0.0f);

LFW::Sprite orangeSprite;
orangeSprite.color = LFW::Colors::Orange;
orangeSprite.SetSize(0.5f, 0.3f);
orangeSprite.SetPosition(0.5f, 0.0f);
```

The sprite size is in 1:1 units from the cameras perspective and not in pixels (with center origin in the middle of the screen (0,0)).

Sprite functionality:
- SetTexture(takes in a filepath or uses the filepath variable as default if no argument is passed)
- color (takes in a glm::vec4 value)
- SetPosition(x, y)
- SetSize(x, y)
- .filePath (to load the texture)
- SetRotation(X, Y, Z)
- pixelated (needs to be set to true if the texture in use is pixelart, else it's set to false as default)

Sprites use "anchors" to manipulate it's orientation in the 2D world. Anchors are just transforms that control position, size and rotation.

This is needed for textures to know the location for their placement. Use it to place objects in your 2d scene.
Remember to render the objects in the correct order as you want to display them.

Examples of how to load the texture of sprites
```cpp

//Using the sprites filepath variable
LFW::Sprite sprite_1;
sprite_1.filePath = "your_filepath_here_with_image_extension";
sprite_1.SetTexture(texturedSprite.filePath);

//Passing it in the function
LFW::Sprite sprite_2;
sprite_2.SetTexture("your_filepath_here_with_image_extension");

//Setting the filepath and then calling the function with no arguments
LFW::Sprite sprite_3;
sprite_3.filePath = "your_filepath_here_with_image_extension";
sprite_3.SetTexture();
```

When they are set up we'll render them from within the main while-loop (after the clear() function and before Display())
```cpp
//Clears screen with color (or black as default)
app.Clear();

//Render the sprite
app.Render(sprite);

//Display graphics
app.Display();
```


## Textures or color
Sprites can load in a texture or a color defined by "spriteName.color = value;"
If a texture filepath is defined, the sprite will always load the texture.
If no filepath is defined the sprite uses the colorvalue (0 by default).
Pre-defined colors can be found in the "LFW::Colors" namespace but you can also define your own with glm::vec4s.

Make sure to have either the texture or color defined before rendering your sprite!



# Spritesheets

LFW now also supports rendering from spritesheets!
The spritesheet needs to initialized, created and loaded.
After the spritesheet has been set, the sprites need to created "manually" and added with the SpriteSheetManager.

Example
```cpp

//Init the spritesheet
LFW::Spritesheet spriteSheet;

//Create the 2D quads from the spritesheet with the SpriteSheetManager. 
//Set spritesheet width & height, sprite width & height,
//number of sprites and if there is any spacing between the sprites(in pixels)
LFW::SpritesheetManager::CreateSpritesheet(spriteSheet, 40, 40, 5, 5, 5, 0);

//Load the spritesheet with the SpriteSheetManager. Takes in the spritesheet, filepath and if the sprites needs pixelation (for pixel art)
LFW::SpritesheetManager::LoadSpritesheet(spriteSheet, "path_to_spritesheet", true);


//Init the sprites to set their size & positions
LFW::Sprite sprite_1;
LFW::Sprite sprite_2;
LFW::Sprite sprite_3;

sprite_1.SetSize(0.3f, 0.3f);
sprite_2.SetSize(0.3f, 0.3f);
sprite_3.SetSize(0.3f, 0.3f);

sprite_1.SetPosition(-0.5f, 0.0f);
sprite_2.SetPosition( 0.0f, 0.0f);
sprite_3.SetPosition( 0.5f, 0.0f);

//Add the sprites to the spritesheet
spriteSheet.AddSprite(sprite_1);
spriteSheet.AddSprite(sprite_2);
spriteSheet.AddSprite(sprite_3);
```

And then in the while-loop you render it as usual with Render() (from the application instance):

```cpp

app.Render(spriteSheet);
```



# Input (keyboard & mouse)

Use "LFW::Input" to access key-pressed or mouse-pressed events.

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
			glm::vec2 newPosition = glm::vec2(orangeSprite.GetPosition());
			newPosition.y += playerSpeed * deltaTime;
			orangeSprite.SetPosition(newPosition.x, newPosition.y);
		}

		//S key for moving down
		else if (LFW::Input::IsKeyPressed(LFW::Key::S))
		{
			glm::vec2 newPosition = glm::vec2(orangeSprite.GetPosition());
			newPosition.y -= playerSpeed * deltaTime;
			orangeSprite.SetPosition(newPosition.x, newPosition.y);
		}

		//A key for moving left
		if (LFW::Input::IsKeyPressed(LFW::Key::A))
		{
			glm::vec2 newPosition = glm::vec2(orangeSprite.GetPosition());
			newPosition.x -= playerSpeed * deltaTime;
			orangeSprite.SetPosition(newPosition.x, newPosition.y);
		}

		//D key for moving right
		else if (LFW::Input::IsKeyPressed(LFW::Key::D))
		{
			glm::vec2 newPosition = glm::vec2(orangeSprite.GetPosition());
			newPosition.x += playerSpeed * deltaTime;
			orangeSprite.SetPosition(newPosition.x, newPosition.y);
		}


		app.Render(orangeSprite);
		app.Display(); 
	}
}
```

This will only work with sprites that's initialized as seperate sprites and not from a spritesheet.
To move sprites that belong to the spritesheet it's needed to acccess the sprite the GetSprite(index) function.
This needs the index number of the sprite (but will be updated later on).
```cpp

glm::vec2 newPosition = glm::vec2(2.0f, 0.0f);

//Since we want to access the first sprite we added, we use '0' as the argument
spriteSheet.GetSprite(0).SetPosition(newPosition.x, newPosition.y);
```



# - Mouse Position

The application can return the mouse position with ScreenToWorld() or WorldToScreen().


## Screen To World

Returns the mouse position (as a glm::vec2 for now, will be replaced with LFW's own vectors later) and converts it from pixels to world units.
Example of usage can be to position a sprite and the mouse location on click or rotating the sprite according to the mouse position.
```cpp
if (LFW::Input::IsMouseButtonPressed(LFW::Mouse::Button0))
{
	glm::vec2 mousePos = app.ScreenToWorldPoint();
	orangeSprite.SetPosition(mousePos.x, mousePos.y);
}

```

## World To Screen

Returns the mouse position (as a glm::vec2 for now, will be replaced with LFW's own vectors later) and converts it from world to pixels with the 0,0 origin in the center instead of in the corner of the screen.



# Camera (Controls & 'Follow')

The application always renderers the sprites using a basic orthographic camera.
It's also possible to set the camera to follow a specific Transform (Anchor).
LFW provides 2 standard cameras, one for the game/application runtime (takes in DeltaTime), and one for debug (not depending on DeltaTime).

Remember that the version for debugging is faster even if the float values is the same for both functions since DeltaTime "normalizes" the speed depending on the "game-ticks".

Reach it from the Application instance. Remember to not use both functions at the same time!
The "Debug" version of the camera controlls is currently using the arrow keys as default while the "Game" version needs custom keys as arguments in the function.

```cpp

//Enables controls for the camera. Current control scheme: Arrow-keys.
//This function needs to have the DeltaTime variable, speed (float) and specified keys passed in (Up, Down, Left, Right).
app.CheckInputForGameCamera(LFW::Key::W, LFW::Key::S, LFW::Key::A, LFW::Key::D, deltaTime, 5.0f);
	
//Enables controls for the camera while debugging (not depending on DeltaTime). Current control scheme: Arrow-keys.
app.CheckInputForDebugCamera(speed);

//Sets the cameras position follow a specified sprites translation in 2D space.
app.SetCameraToFollowTransform(orangeSprite.GetTranslation());

```


# Math Library

LFWs own implementation of vectors.
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
	
 //CLAMP()
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
 LFW::MathF::Floor(10.7f);  //Prints 10



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



# AudioEngine

This part of the framework is currently heavily in development to get the API right and to have the functionality required.
Currently it supports playing audio from files, looping, setting the volume and saving the filepath in my own basic resource manager.

Basic example:
```cpp

//Instantiate the engine
LFW::AudioEngine engine;

//Sets the master volume with an integer. 0 is silent, 1 is "max"
engine.SetMasterVolume(value);

//Play a .wav file from source, plays once (uses miniaudios ma_engine)
engine.PlayAudioFromFile("filepath");

//Play a .wav file from source, loops (uses miniaudios ma_device)
engine.PlayAudioWithLooping("filepath");

//Add a single const char* filePath to a sound file to an unordered map with a specified key. WIP.
engine.AddSoundToMap(key, value);

//Retrieves a const char* value with a specified key. WIP.
engine.GetSoundFromMap(key);
```



# Features Soon To Come

- [x] Screen to world Point
- [x] World to screen Point (in pixels)
- [x] Support for spritesheets
- [ ] Fonts
- [ ] Sprite batching



# Disclaimer

This repo and documentation is heavily in progress and will be frequently changed!

Thank you for checking it out!