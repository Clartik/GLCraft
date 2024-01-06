project "Glad"
   kind "StaticLib"
   language "C"

   files { "**.h", "**.c" }

   filter "system:windows"
       systemversion "latest"