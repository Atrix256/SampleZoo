workspace "SampleZoo"
	configurations {"Debug", "Release"}
	platforms { "Win64", "Win32" }
	location "build"

project "SampleZoo"
	kind "ConsoleApp"
	language "C++"
	targetdir "build/bin/%{cfg.builfcfg}"

	debugdir "./"

	includedirs { "src/" }

	files {"src/**.h", "src/**.cpp"}

	filter { "platforms:Win32" }
    	system "Windows"
    	architecture "x32"

	filter { "platforms:Win64" }
    	system "Windows"
    	architecture "x64"	

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "on"