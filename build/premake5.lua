-- premake5.lua
ROOT = "%{wks.location}"
WORKSPACE = "parrot"
STARTUP_PROJECT = "demo"

-- workspace
workspace(WORKSPACE)
   -- startproject
   startproject(STARTUP_PROJECT)
   
   -- location
   location ".."

   -- cpp
   language "C++"
   cppdialect "C++20"
   debugger "GDB"
   warnings "High"

   -- defines
   defines {
      "PARROT_GLFW",
      "PARROT_OPENGL"
   }
   
   -- dependancies
   -- :: directories
   libdirs {
      ROOT .. "/vendor/**/lib"
      --[[ INSERT ADDITIONAL LINKS HERE ]]
   }

   -- config
   configurations { "debug", "release" }
   -- :: debug
   filter "configurations:debug"
      -- symbols / defines
      symbols "On"
      defines { "CONFIG_DEBUG" }
      -- options
      linkoptions { }
   -- :: dist
   filter "configurations:release"
      -- optimize / defines
      optimize "On"
      defines { "CONFIG_RELEASE" }
      -- options
      linkoptions { "-Ofast" }

   -- system
   -- :: windows
   filter "system:windows"
      defines { "SYSTEM_WINDOWS" }
   -- :: linux
   filter "system:linux"
      defines { "SYSTEM_LINUX" }

-- project lib
project(WORKSPACE)
   -- static lib
   kind "StaticLib"

   -- precompiled headers
   pchheader "common.hh"
   pchsource "common.cc"
   
   -- include
   includedirs {
      ROOT .. "/src",
      ROOT .. "/vendor/"
   }
   -- files
   files {
      ROOT .. "/src/**",
      ROOT .. "/vendor/**",
   }

   -- binaries
   targetdir(ROOT .. "/bin/%{cfg.buildcfg}")
   objdir(ROOT .. "/bin/obj")

-- project demo
project "demo"
   -- console
   kind "ConsoleApp"

   -- include
   includedirs {
      ROOT .. "/src",
      ROOT .. "/vendor/",
      ROOT .. "/example/demo/"
      --[[ INSERT ADDITIONAL DIRECTORIES HERE ]]
   }
   -- files
   files {
      ROOT .. "/example/demo/**",
      --[[ INSERT ADDITIONAL FILES HERE ]]
   }

   -- dependancies
   -- :: directories
   libdirs {
      ROOT .. "/bin/%{cfg.buildcfg}",
      ROOT .. "/vendor/**/lib"
      --[[ INSERT ADDITIONAL DIRECTORIES HERE ]]
   }
   -- :: libraries
   links { WORKSPACE, "glfw3.lib", "opengl32.lib" --[[ INSERT ADDITIONAL LINKS HERE ]] }

   -- binaries
   targetdir(ROOT .. "/bin/%{cfg.buildcfg}")
   objdir(ROOT .. "/bin/obj")