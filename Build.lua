-- premake5.lua
workspace "GLCraft"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "Engine/Build-Engine.lua"
group "Core/Dependencies"
   include "Engine/Vendor/Glad/Build-Glad.lua"
group ""

include "App/Build-App.lua"