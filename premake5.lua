workspace "Ray Marching"
    architecture "x64"
    startproject "Ray Marching"
    configurations { "Debug", "Release" }

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    project "Ray Marching"
        location "Ray Marching"
        kind "ConsoleApp"
        language "C++"

        targetdir("bin/"..outputdir.."/%{prj.name}")
        objdir("bin-int/"..outputdir.."/%{prj.name}")

        files { "**.h", "**.cpp", "**.c" }

        includedirs {"Ray Marching/libraries/include"}
        libdirs {"Ray Marching/libraries/lib"} 

        links {"glfw3"}

        filter "configurations:Debug"
            defines { "DEBUG" }
            symbols "On"

        filter "configurations:Release"
            defines { "NDEBUG" }
            optimize "On"
