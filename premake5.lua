workspace "Ray Marching"
    architecture "x64"
    startproject "Ray Marching"
    configurations { "Debug", "Release" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "Ray Marching"
        location "Ray Marching" -- this line sets the location for the generated project files
        kind "ConsoleApp"
        language "C++"
	cppdialect "C++20"

        targetdir("bin/"..outputdir.."/%{prj.name}")
        objdir("bin-int/"..outputdir.."/%{prj.name}")

        files { "**.h", "**.cpp", "**.c" } -- this line sets the relative path to the source files

        includedirs {"Ray Marching/libraries/include"} -- this line sets the path to the include files
        libdirs {"Ray Marching/libraries/lib"} -- this line sets the path to the library files

        links {"glfw3"} -- this line links the GLFW library

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
