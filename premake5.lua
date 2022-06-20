include "Dependencies.lua"

workspace "LunaFramework"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "LFW/Vendor/GLFW"
	include "LFW/Vendor/Glad"
	include "LFW/Vendor/imgui"
	-- Don't include glm here!
group ""

include "LFW"
include "Sandbox"