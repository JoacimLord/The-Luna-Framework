#pragma once
#include "LFWpch.h"
#include "LunaAPI/Utility/Debug.h"
#include <backends/imgui_impl_glfw.h> 
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

namespace LFW {

	std::vector<ImVec4> colors;
	std::vector<std::string> msgs;
	std::vector<const char*> c_msgs;

	ImVec4 red = { 1.0f, 0.0f, 0.0f, 1.0f };
	ImVec4 orange = { 1.0f, .5f, 0.0f, 1.0f };
	ImVec4 yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
	ImVec4 green = { 0.0f, 1.0f, 0.0f, 1.0f };
	ImVec4 white = { 1.0f, 1.0f, 1.0f, 1.0f };

	void Debug::Log(std::string& msg)
	{
		c_msgs.push_back(msg.c_str());
		colors.push_back(white);
	}
	void Debug::Log(const char* msg)
	{
		c_msgs.push_back(msg);
		colors.push_back(white);
	}
	void Debug::Log(std::string& msg, int clr)
	{
		c_msgs.push_back(msg.c_str());

		//Switch()
		if (clr == 0)
		{
			colors.push_back(green);
		}

		if (clr == 1)
		{
			colors.push_back(yellow);
		}

		if (clr == 2)
		{
			colors.push_back(orange);
		}

		if (clr == 3)
		{
			colors.push_back(red);
		}
	}
	void Debug::Log(const char* msg, int clr)
	{
		c_msgs.push_back(msg);

		//Switch()
		if (clr == 0)
		{
			colors.push_back(green);
		}

		if (clr == 1)
		{
			colors.push_back(yellow);
		}

		if (clr == 2)
		{
			colors.push_back(orange);
		}

		if (clr == 3)
		{
			colors.push_back(red);
		}
	}
	void Debug::BuildLogWindow()
	{
		//CONSOLE WINDOW
		ImGui::Begin("Debug Console");
		ImGui::Text("Debug Console");

		if (ImGui::Button("Reset Console Log"))
		{
			//Add a reset() function to namespace
			colors.clear();
			c_msgs.clear();
		}
		if (c_msgs.size() > 0)
		{
			for (int i = 0; i < c_msgs.size(); i++)
			{
				ImGui::TextColored(colors[i], c_msgs[i]);
			}
		}
		ImGui::End();
	}
}
