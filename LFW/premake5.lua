project "LFW"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "LFWpch.h"
	pchsource "src/LFWpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
		
		"Vendor/stb_image/**.h",
		"Vendor/stb_image/**.cpp",
		"Vendor/glm/glm/**.hpp",
		"Vendor/glm/glm/**.inl",
		"Vendor/miniaudio/**.h",
		"Vendor/miniaudio/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.miniaudio}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}


	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

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

