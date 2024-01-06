project "Glad"
   kind "StaticLib"
   language "C"
   staticruntime "off"

   files { "**.h", "**.c" }

   includedirs
   {
      "include"
   }

   targetdir ("Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"