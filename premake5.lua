workspace "ProceduralTerrainDemo"
    architecture "x64"
    startproject "ProceduralTerrainDemo"

    configurations { "Debug", "Release" }
    flags { "MultiProcessorCompile" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "ProceduralTerrainDemo"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "src/**.cpp",
        "include/**.h",
        "include/**.hpp"
    }

    includedirs {
        "include",
        "vendor/glfw-3.4/include",
        "vendor/glew-2.2.0/include"
    }

    libdirs {
        "vendor/glfw-3.4/lib",
        "vendor/glew-2.2.0/lib"
    }

    links {
        "glfw3.lib",
        "glew32s.lib",
        "opengl32.lib"
    }

    defines {
        "GLEW_STATIC"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        runtime "Release"
        optimize "On"
