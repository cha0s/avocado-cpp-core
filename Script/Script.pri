include(../SPI.pri)

win32 {

	SOURCES += \
		\
		../../../core/FS.cpp \
		\
		../../../core/Script/Script.cpp ../../../core/Script/ScriptService.cpp \
		\
		../../../core/Core/CoreService.cpp \
		\
		../../../core/Graphics/GraphicsService.cpp \
		../../../core/Graphics/Canvas.cpp ../../../core/Graphics/Font.cpp \
		../../../core/Graphics/Image.cpp ../../../core/Graphics/Window.cpp \
		\
		../../../core/Sound/SoundService.cpp ../../../core/Sound/Sample.cpp \
		../../../core/Sound/Music.cpp \
		\
		../../../core/Timing/TimingService.cpp ../../../core/Timing/Counter.cpp

	LIBS += -lboost_system -lboost_filesystem -lboost_regex

}

HEADERS += \
	\
	../../../Factory.h \
	\
	../../../FS.h \
	\
	../../../Abstract/Script/Script.h ../../Abstract/Script/ScriptService.h \
	\
	../../../Abstract/Graphics/GraphicsService.h ../../../Abstract/Graphics/Font.h ../../../Abstract/Graphics/Image.h ../../../Abstract/Graphics/Window.h \
	\
	../../../Abstract/Timing/Counter.h \
	\
	../../../Abstract/Core/CoreService.h
