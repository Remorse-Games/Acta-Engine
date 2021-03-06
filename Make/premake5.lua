workspace "Acta"
	location ".."
	architecture "x64"
	startproject "Game"
	
	configurations
	{
		"Debug",
		"Develop",
		"Release"
	}

trunk = "../"

-- struct to easier include dir rather than using path
IncludeDir = {}
IncludeDir["GLFW"] 		= 	(trunk .. "Externals/glfw/include")
IncludeDir["Glad"] 		= 	(trunk .. "Externals/glad/include")
IncludeDir["ImGui"] 	= 	(trunk .. "Externals/imgui")
IncludeDir["glm"] 		= 	(trunk .. "Externals/glm")
IncludeDir["stb_image"] = 	(trunk .. "Externals/stb_image")
IncludeDir["spdlog"] 	= 	(trunk .. "Externals/spdlog/include")
IncludeDir["catch"] 	= 	(trunk .. "Externals/Catch2")
IncludeDir["assimp"] 	= 	(trunk .. "Externals/assimp/include")


-- output name for bin / obj
outputName = "/%{cfg.system}__%{cfg.buildcfg}__%{cfg.architecture}"

-- take another premake to build the project
include (trunk .. "Externals/imgui/project")
include (trunk .. "Externals/glad/project")
include (trunk .. "Externals/glfw/project")

-------------------------------------------------------------------------------------
------------------------ Engine project ---------------------------------------------	
-------------------------------------------------------------------------------------

project "Acta"
	location (trunk .. "Engine")
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir (trunk .. "%{prj.name}/bin/" .. outputName)
	objdir (trunk .. "%{prj.name}/obj/" .. outputName)

	-- use precompile header
	pchheader "actapch.h"
	pchsource (trunk .. "Engine/Source/actapch.cpp")
	
	
	files
	{
		(trunk .. "Engine/Source/**.h"),
		(trunk .. "Engine/Source/**.cpp"),
		(trunk .. "Externals/stb_image/**.cpp"),
		(trunk .. "Externals/stb_image/**.h"),
		(trunk .. "Externals/glm/glm/**.hpp"),		
		(trunk .. "Externals/glm/glm/**.inl"),
		(trunk .. "Externals/Catch2/**.hpp")
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	
	includedirs
	{
		(trunk .. "Engine/Source"),
		--(trunk .. "Externals"),
		(trunk .. "Externals/spdlog/include"),
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.catch}",
		"%{IncludeDir.assimp}"
	}
	
	libdirs
	{
		(trunk .. "Externals/assimp/lib");
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"assimp-vc143-mt.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		-- preprocessor definition
	defines
	{
		--"_CRT_SECURE_NO_WARNINGS"
	}
	
	filter "configurations:Debug"
		defines "ACTA_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Develop"
		defines "ACTA_DEV"
		runtime "Release"
		optimize "on"	

	filter "configurations:Release"
		defines "ACTA_RELEASE"
		runtime "Release"
		optimize "on"
		
-------------------------------------------------------------------------------------
------------------------ Game project ---------------------------------------------	
-------------------------------------------------------------------------------------

project "Game"
	location (trunk .. "Project")
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir (trunk .. "%{prj.name}/bin/" .. outputName)
	objdir (trunk .. "%{prj.name}/obj/" .. outputName)
	
	prelinkcommands {
	"{COPY} ../Externals/assimp/dlls/assimp-vc143-mt.dll ../%{prj.name}/bin/" .. outputName
	}

	files
	{
		(trunk .. "Project/Source/**.h"),
		(trunk .. "Project/Source/**.cpp"),
		(trunk .. "Externals/Catch2/**.hpp")
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	
	includedirs
	{
		(trunk .. "Engine/Source"),
		(trunk .. "Externals"),
		(trunk .. "Externals/spdlog/include"),
        (trunk .. "Externals/assimp"),
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.catch}",
		"%{IncludeDir.assimp}"
	}
	
	links
	{
		"Acta"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		-- preprocessor definition
	defines
	{
		--"_CRT_SECURE_NO_WARNINGS"
	}
	
	filter "configurations:Debug"
		defines "ACTA_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Develop"
		defines "ACTA_DEV"
		runtime "Release"
		optimize "on"	

	filter "configurations:Release"
		defines "ACTA_RELEASE"
		runtime "Release"
		optimize "on"