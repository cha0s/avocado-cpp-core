include(../SPI.pri)

win32 {

	SOURCES += \
		\
		../../../core/FS.cpp \
		\
		../../../core/Sound/SoundService.cpp ../../../core/Sound/Sample.cpp \
		../../../core/Sound/Music.cpp

	LIBS += -lboost_system -lboost_filesystem -lboost_regex

}

HEADERS += \
	\
	../../../core/Factory.h ../../../core/FS.h ../../ResourceManager.h \
	\
	../SoundService.h ../Sample.h ../Music.h
