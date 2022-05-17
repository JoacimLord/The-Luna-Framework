#include "Luna.h"
#include <imgui/imgui.h>



//States for directions
enum class HorizontalDirection
{
	Idle = 0,

	Left,
	Right
};

enum class VerticalDirection
{
	Idle = 0,

	Up,
	Down
};

struct Entity
{
	Luna::Anchor anchor; 

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

	//Only for ball but it will do for now to have it in every Entity obj.
	HorizontalDirection direction = HorizontalDirection::Left;
	VerticalDirection height = VerticalDirection::Down;
};


float bounceCounter = 0;

void Luna::Application::BuildUI()
{
	ImGui::Begin("Instructions");
	ImGui::Text("Move the paddle with W, A, S, D");
	ImGui::Text("Make the ball bounce on the wall to gain points!");

	ImGui::End();
	ImGui::Begin("SCOREBOARD");
	ImGui::Text("Score: %.0f", bounceCounter);
	ImGui::End();
}

//Change these to root for the project, not solution!
const char* filepathBG = "Resources/bg.png";
const char* filepathBlue = "Resources/blue.png";
const char* filepathpaddle = "Resources/paddle.png";
const char* filepathBall = "Resources/ball.png";

bool CalculateCollision(Luna::Anchor& a, Luna::Anchor& b)
{
	bool collisionX = a.Translation.x + a.Scale.x >= b.Translation.x &&
		b.Translation.x + b.Scale.x >= a.Translation.x;

	bool collisionY = a.Translation.y + a.Scale.y >= b.Translation.y &&
		b.Translation.y + b.Scale.y >= a.Translation.y;

	return collisionX && collisionY;
}


int main()
{
	Luna::Application app("Solo-Paddle made in with The Luna Framework"); //RENAME

	//Abstraction in progress, how to load textures.
	std::shared_ptr<Luna::Texture> backdrop = std::make_shared<Luna::Texture>(filepathBG);
	std::shared_ptr<Luna::Texture> paddle1 = std::make_shared<Luna::Texture>(filepathpaddle);
	std::shared_ptr<Luna::Texture> ball = std::make_shared<Luna::Texture>(filepathBall);
	std::shared_ptr<Luna::Texture> wall = std::make_shared<Luna::Texture>(filepathBlue);


	//Init positions for textures -----------------------------------------------------------------------------------------
	Entity bg;
	bg.SetSize(1500.0f, 800.0f);
	bg.SetPosition(600.0f, 350.0f);

	Entity bluePaddle;
	bluePaddle.SetSize(30.0f, 100.0f);
	bluePaddle.SetPosition(100.0f, 350.0f);

	Entity redBall;
	redBall.SetSize(30.0f, 30.0f);
	redBall.SetPosition(1100.0f, 350.0f);
	
	Entity wallPos;
	wallPos.SetSize(50.0f, 800.0f);
	wallPos.SetPosition(1200.0f, 350.0f);
	

	float m_LastFrameTime = 0.0f;
	float xSpeed = 8;
	float ySpeed = 1.5f;

	while (app.IsRunning())
	{
		float elapsedTime = app.GetElapesedRuntime();
		Luna::DeltaTime deltaTime = elapsedTime - m_LastFrameTime;
		m_LastFrameTime = elapsedTime;

		//Random number between 0 and 1, decides the direction of the ball bounce :>
		int temp = std::rand() % 2;

		//If paddle is out of bounds
		if ((bluePaddle.anchor.Translation.x < 0) || (bluePaddle.anchor.Translation.x > 1151) ||
			(bluePaddle.anchor.Translation.y > 700) || (bluePaddle.anchor.Translation.y < 0))
		{
			std::cout << "Paddle out of bounds, resetting!\n";
			bluePaddle.SetPosition(100.0f, 350.0f);
		}

		//If ball is out of bounds
		if ((redBall.anchor.Translation.x < 0) || (redBall.anchor.Translation.x > 1200) ||
			(redBall.anchor.Translation.y > 700) || (redBall.anchor.Translation.y < 0))
		{

			bounceCounter = 0;
			redBall.SetPosition(1100.0f, 350.0f);
		}

		//CHECK DIRECTION 
		if (CalculateCollision(wallPos.anchor, redBall.anchor) || redBall.anchor.Translation.x > 1150) //Collision OR ball going over wall edge
		{
			bounceCounter++;
			std::cout << "Point gained!\n";

			std::cout << "Current points: " << bounceCounter << "\n";

			redBall.direction = HorizontalDirection::Left;

			//random directon
			if (temp == 1)
			{
				redBall.height = VerticalDirection::Up;
			}
			else if (temp == 0)
			{
				redBall.height = VerticalDirection::Down;
			}
		} 

		if (CalculateCollision(bluePaddle.anchor, redBall.anchor))
		{
			redBall.direction = HorizontalDirection::Right;
			
			if (redBall.anchor.Translation.y > bluePaddle.anchor.Translation.y)
			{
				std::cout << "Ball hit the higher half of the paddle\n";
				std::cout << "Ball going higher\n";
				redBall.height = VerticalDirection::Up;
			} 
			else if (redBall.anchor.Translation.y < bluePaddle.anchor.Translation.y)
			{
				std::cout << "Ball hit the lower half of the paddle\n";
				std::cout << "Ball going lower\n";
				redBall.height = VerticalDirection::Down;
			}
		}

		//Direction and speed of ball
		if(redBall.direction == HorizontalDirection::Left)
		{
			redBall.anchor.Translation.x -= xSpeed;
		}
		else if (redBall.direction == HorizontalDirection::Right)
		{
			redBall.anchor.Translation.x += xSpeed;
		}

		if (redBall.height == VerticalDirection::Up)
		{
			redBall.anchor.Translation.y += ySpeed;
		}
		else if (redBall.height == VerticalDirection::Down)
		{
			redBall.anchor.Translation.y -= ySpeed;
		}
		
		//Paddle movement
		if (Luna::Input::IsKeyPressed(Luna::Key::W)) { bluePaddle.anchor.Translation.y += 5; }
		else if (Luna::Input::IsKeyPressed(Luna::Key::S)) { bluePaddle.anchor.Translation.y -= 5; }
		
		if (Luna::Input::IsKeyPressed(Luna::Key::D)) { bluePaddle.anchor.Translation.x += 5; }
		else if (Luna::Input::IsKeyPressed(Luna::Key::A)) { bluePaddle.anchor.Translation.x -= 5; }


		//=========================================
		//			MOUSE CLICK EXAMPLE
		//=========================================

		//Example of interaction (can drag the paddle with left mouse click)
		if (Luna::Input::IsMouseButtonPressed(Luna::Mouse::ButtonLeft))
		{
			//Create an anchor for the mouse to "hold on to", and for the collision function argument.
			Luna::Anchor mouseCursor;

			//Make it a little bit wider just for this example
			mouseCursor.Scale.x = 30;
			mouseCursor.Scale.y = 30;

			mouseCursor.Translation.x = Luna::Input::GetMousePositionX();
			mouseCursor.Translation.y = Luna::Input::GetMousePositionY(); //This gets reversed for some reason, WIP.

			if (CalculateCollision(mouseCursor, bluePaddle.anchor))
			{
				bluePaddle.anchor.Translation.x = Luna::Input::GetMousePositionX();
				bluePaddle.anchor.Translation.y = Luna::Input::GetMousePositionY();
			}
		}

		//Render everything
		app.Clear(1.0f, 0.0f, 1.0f, 1.0f);

		app.Render(backdrop, bg.anchor.GetTransform());			//Background
		app.Render(paddle1, bluePaddle.anchor.GetTransform());  //Right paddle (blue)
		app.Render(ball, redBall.anchor.GetTransform());  //Right paddle (blue)
		app.Render(wall, wallPos.anchor.GetTransform());  //Wall

		app.Display();
		app.Update();
	}
}