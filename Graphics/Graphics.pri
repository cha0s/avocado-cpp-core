include(../SPI.pri)

win32 {

	SOURCES += \
		\
		../../../core/FS.cpp \
		\
		../../../core/Graphics/GraphicsService.cpp \
		../../../core/Graphics/Canvas.cpp ../../../core/Graphics/Font.cpp \
		../../../core/Graphics/Image.cpp ../../../core/Graphics/Window.cpp
	
	LIBS += -lboost_system -lboost_filesystem -lboost_regex

}

HEADERS += \
	\
	../../../Factory.h ../../../FS.h ../../ResourceManager.h \
	\
	../GraphicsService.h ../Canvas.h ../Font.h ../Image.h ../Window.h
