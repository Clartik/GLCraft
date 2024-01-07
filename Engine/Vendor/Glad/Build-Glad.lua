project "GLAD"
   kind "StaticLib"
   language "C"
   staticruntime "off"

   files { "**.h", "**.c" }

   includedirs
   {
      "include"
   }

   targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("bin/int/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"