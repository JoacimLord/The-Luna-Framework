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
	
	--solution_items
	--{
	--	".editorconfig"
	--}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	--include "Vendor/"
	include "Luna/Vendor/GLFW"
	include "Luna/Vendor/Glad"
	include "Luna/Vendor/imgui"
	-- Don't include glm here!
group ""

include "Luna"
include "Sandbox"