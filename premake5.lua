workspace "SampleZoo"
	configurations {"Debug", "Release"}

project "SampleZoo"
	kind "ConsoleApp"
	language "C++"
	targetdir "bin/%{cfg.builfcfg}"

	files {"**.h", "**.cpp"}

	filter "configurations:Debug"
		defines {"DEBUG"}
		symbols "On"

	filter "configurations:Release"
		defines {"NDEBUG"}
		optimize "on"