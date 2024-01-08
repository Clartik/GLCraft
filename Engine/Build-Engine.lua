project "Engine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp" }

   pchheader "pch.h"
   pchsource "src/pch.cpp"

   defines 
   {
      "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
   }

   includedirs
   {
      "src",
      "../vendor/glm",
      "vendor/GLFW/include",
      "vendor/GLAD/include",
      "vendor/spdlog/include"
   }

   links
   {
      "GLAD",
      "vendor/GLFW/lib-vc2022/glfw3.lib"
   }

   targetdir ("../bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("../bin/int/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       defines { "DEBUG", "ENABLE_ASSERTS" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"