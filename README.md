# The-Luna-Framework
"Low level" framework based on the API of the "Luna Engine" (currently in development)

"The Luna Framework" is a small extracted portion of the API from my other project ("Luna Engine") that I'm currently working on in my spare time.
Luna Engine currently supports scene management, has it's own ECS that I've written from scratch, a fully functional editor and more. 
This project uses the engines rendering (written with opengl) and also supports the integration of your own UI with the help of ImGui.
It's aimed for you that want to have a small framework to get you started with rendering something to your screen.

The intention of this framework is to build any kind of GUI app, but it's probably most suitable for simple 2d games for now.
Only supports graphics and GUI, audio wil be added in the future.

The API is heavily based on SFML with a similar setup for you main loop and rendering (examples of how you get started is in the Main.cpp file in the Sandbox project).
The framework always renders graphics to a framebuffer that then displays it in a ImGui window called "Viewport". 
If you don't want to use opengl for graphics and only intends to create a ImGui only app, feel free to just use the viewport as your main window. 
Support of turning of the viewport will come in a later update.


Third party libraries in use:

- Glad
- imgui
- GLFW
- glm
- stb_image


How to get started

Simply clone or download the project. Run the Setup.bat file to generate your solution and get started.
The only file that you need to include is the "Luna.h" header file.

Feel free to use the Sandbox project as your starting point.
The framework currently only supports development for Windows.


- API DOC -

```cpp
/* This includes the whole framework */
#include "Luna.h"

/* This need to be included for ImGui usage */
#include <imgui/imgui.h>

int main()
{
	/* How to initalize a window and name it */
	Luna::Application app("App"); 

	/* Move directly into the while-loop, app.IsRunning() needs to be included here */
	while (app.IsRunning())
	{
		/* These two are for rendering opengl in the viewport (graphics) */
		app.Clear(1.0f, 0.0f, 1.0f, 1.0f); //Initializes the viewport as a rendering texture
		app.Render(); //To render graphics to the viewport, takes in a texture and a anchor.GetTransform().

		/* If your application only need the ImGui setup, only keep this and Update */
		app.Display(); 
		app.Update(); 
	}
}

```

An anchor is just a transform with a scale, translation and rotation combined.
It needs to be instantiated to be used as a point of reference for your actual texture, use it to place objects in your 2d scene.
The texture needs to be a pointer, will add support later to have it on the stack.
Remember to render the objects in the correct order as you want to display them.

For example if you're rendering game objects:

1. Background
2. Props that is walkable
3. Player
4. Enemies
5. Trees that's supposed to cover the characters

etc...


ANCHOR & TEXTURE EXAMPLE

```cpp
#include "Luna.h"

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

int main()
{
	/* How to initalize a window and name it */
	Luna::Application app("App"); 

	std::shared_ptr<Luna::Texture> texture = std::make_shared<Luna::Texture>(filepath);

	ExampleObject object;
	object.SetSize(50.0f, 50.0f);
	object.SetPosition(600.0f, 350.0f);

	/* Move directly into the while-loop, app.IsRunning() needs to be included here */
	while (app.IsRunning())
	{
		if (Luna::Input::IsKeyPressed(Luna::Key::Z))
		{
			object.anchor.Translation.x += 10.0f;
		}

		app.Clear(1.0f, 0.0f, 1.0f, 1.0f);

		app.Render(texture, object.anchor.GetTransform()); //Renders the texture at the anchors position and with the anchors scale.
		
		app.Display();
		app.Update();
	}
}

```


Thanks for using my framework in your own project <3
