TEMPLATE = lib

CONFIG -= qt
CONFIG += dll

win32 {
	debug {
		QMAKE_POST_LINK = cp debug/$(TARGET) $${TARGET}.spii
	}
	else {
		QMAKE_POST_LINK = cp release/$(TARGET) $${TARGET}.spii
	}
}
else {
	QMAKE_POST_LINK = cp $(TARGET) $${TARGET}.spii
}

PRECOMPILED_HEADER = ../../../core/avocado-global.h

!debug {
	CONFIG += silent
	QMAKE_LFLAGS += -g
}

SOURCES += implementSpi.cpp

HEADERS += ../../../core/avocado-global.h

INCLUDEPATH += ../../.. ../../../core/deps

win32 {
	debug {
		LIBS += -L../../../core/debug
	}
	else {
		LIBS += -L../../../core/release
	}
}
else {
	LIBS += -L../../../core
}

LIBS += -lavocado

win32:OUT_DIR = obj/win32
unix:OUT_DIR = obj/unix

OBJECTS_DIR = $$OUT_DIR

unix:QMAKE_CXXFLAGS += -ansi -Werror

spii.path = ../../../SPII
spii.files += $${TARGET}.spii
INSTALLS += spii
