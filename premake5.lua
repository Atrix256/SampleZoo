dofile("codegen.lua")
dofile("docgen.lua")
print "=====Generating Projects and Solution====="

workspace "SampleZoo"
	configurations {"Debug", "Release"}
	platforms { "Win64", "Win32" }
	location "build"

project "SampleZoo"
	kind "ConsoleApp"
	language "C++"
	targetdir "build/bin/%{cfg.builfcfg}"

	debugdir "./"

	includedirs { "src/", "build/codegen/" }

	files {"src/**.h", "src/**.cpp", "src/**.lua", "src/**.md", "build/codegen/**.h", "build/codegen/**.cpp"}

	filter "files:**.lua"
		buildaction "None"

	filter "files:**.md"
		buildaction "None"

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