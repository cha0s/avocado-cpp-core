include(../SPI.pri)

win32 {

	SOURCES += \
		\
		../../../core/Timing/TimingService.cpp ../../../core/Timing/Counter.cpp

}

HEADERS += \
	\
	../../../Factory.h \
	\
	../TimingService.h ../Counter.h
