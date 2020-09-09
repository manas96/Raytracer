workspace "Raytracer"
    architecture "x64"

    -- Only need debug configuration for this
    configurations
    {
        "Debug"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "Raytracer"
    -- Makes sure all following paths are relative to Raytracer
    kind "ConsoleApp"
    language "C++"
    
    objdir("Raytracer/obj")
    targetdir("Raytracer/bin")

    files
    {
        "include/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "libs/**",
        "include/"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

    filter "configurations:Debug"
        symbols "On"
