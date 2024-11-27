-- premake5.lua
ROOT = ".."
EXAMPLE = "example_demo"

-- workspace
workspace "parrot"
   -- basic
   location (ROOT)
   startproject (EXAMPLE)

   -- c++
   language "C++"
   cppdialect "C++20"
   warnings "High"

   -- defines
   defines {
      "PARROT_GLFW", -- WINDOW_API
      "PARROT_OPENGL" -- GRAPHICS_API
   }
   
   -- dependencies
   -- :: directories
   libdirs {
      ROOT .. "/bin/%{cfg.buildcfg}",
      ROOT .. "/vendor/**/lib"
   }
   -- :: libraries
   links {
      "glfw3", -- WINDOW_API
      "opengl32" -- GRAPHICS_API
   }

   -- system
   -- :: windows
   filter "system:windows"
      defines { "SYSTEM_WINDOWS" }
   filter {}
   -- :: linux
   filter "system:linux"
      defines { "SYSTEM_LINUX" }
   filter {}

   -- config
   configurations { "debug", "release" }
   -- :: debug
   filter { "configurations:debug" }
      defines { "CONFIG_DEBUG" }
      symbols "On"
      linkoptions {}
   filter {}
   -- :: release
   filter { "configurations:release" }
      defines { "CONFIG_RELEASE" }
      optimize "On"
      linkoptions { "-Ofast" }
   filter {}

   -- out
   targetdir (ROOT .. "/bin/%{cfg.buildcfg}")
   objdir (ROOT .. "/build/obj")
   
-- vendor
project "vendor"
   -- basic
   location (ROOT .. "/vendor")
   kind "StaticLib"

   -- include
   includedirs {
      ROOT .. "/vendor/"
   }
   -- files
   files {
      ROOT .. "/vendor/**",
   }

-- parrot
project "parrot"
   -- basic
   location (ROOT .. "/src")
   kind "StaticLib"

   -- precompiled headers
   pchheader "common.hh"
   pchsource (ROOT .. "src/common.cc")
   
   -- include
   includedirs {
      ROOT .. "/src",
      ROOT .. "/vendor/"
   }
   -- files
   files {
      ROOT .. "/src/**",
   }

-- example_demo
project "example_demo"
   -- basic
   location (ROOT .. "/example/demo")
   kind "ConsoleApp"

   -- include
   includedirs {
      ROOT .. "/src",
      ROOT .. "/vendor/",
      ROOT .. "/example/demo/"
   }
   -- files
   files {
      ROOT .. "/example/demo/**",
   }

   -- libraries
   links { "parrot", "vendor" }