
project(avocado)

include(./CMakeLists-core.txt)

include_directories(deps ..)

add_library(avocado SHARED

	FS.cpp
	
	Script/Script.cpp
	Script/ScriptService.cpp
	
	Core/CoreService.cpp
	
	Graphics/GraphicsService.cpp
	Graphics/Canvas.cpp
	Graphics/Font.cpp
	Graphics/Image.cpp
	Graphics/Sprite.cpp
	Graphics/Window.cpp
	
	Timing/TimingService.cpp
	Timing/Counter.cpp
	
	Sound/SoundService.cpp
	Sound/Sample.cpp
	Sound/Music.cpp
	
)

target_link_libraries(avocado
	boost_filesystem boost_regex boost_system dl
)
