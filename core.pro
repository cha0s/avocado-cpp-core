TARGET = avocado
TEMPLATE = lib

CONFIG -= qt
CONFIG += dll
CONFIG += plugin

PRECOMPILED_HEADER = avocado-global.h

!debug {
	CONFIG += silent
	QMAKE_LFLAGS += -g
}

SOURCES += \
	\
	FS.cpp \
	\
	Script/Script.cpp Script/ScriptService.cpp \
	Core/CoreService.cpp \
	Graphics/GraphicsService.cpp Graphics/Canvas.cpp Graphics/Font.cpp Graphics/Image.cpp Graphics/Sprite.cpp Graphics/Window.cpp \
	Timing/TimingService.cpp Timing/Counter.cpp \
	Sound/SoundService.cpp Sound/Sample.cpp Sound/Music.cpp

HEADERS += \
	\
	avocado-global.h \
	\
	Factory.h \
	\
	FS.h \
	\
	SpiiLoader.h \
	Script/Script.h Script/ScriptService.h \
	Core/CoreService.h \
	Graphics/GraphicsService.h Graphics/Canvas.h Graphics/Font.h Graphics/Image.h Graphics/Sprite.h Graphics/Window.h \
	Timing/TimingService.h Timing/Counter.h \ 
	Sound/SoundService.h Sound/Sample.h Sound/Music.h

INCLUDEPATH += deps ..

win32 {
	LIBS += -Wl,--whole-archive -ldl -Wl,--no-whole-archive
}
LIBS += -lboost_filesystem -lboost_regex -lboost_system

win32:OUT_DIR = obj/win32
unix:OUT_DIR = obj/unix

OBJECTS_DIR = $$OUT_DIR

unix:QMAKE_CXXFLAGS += -ansi -Werror

core.path = ..
win32 {
	debug {
		core.files += debug/avocado.dll
	}
	else {
		core.files += release/avocado.dll
	}
}
else {
	core.files += libavocado.so
}
INSTALLS += core
