project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Luna/src",
		"%{wks.location}/Luna/Vendor",
		"%{wks.location}/Luna/Vendor/GLFW/include",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Luna"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "LUNA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LUNA_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LUNA_DIST"
		runtime "Release"
		optimize "on"