#-------------------------------------------------
#
# Project created by QtCreator 2021-08-30T09:10:59
#
#-------------------------------------------------

QT       += widgets sql xml xmlpatterns

TARGET = Analysis
TEMPLATE = lib

DEFINES += ANALYSIS_LIBRARY

INCLUDEPATH += \
            $$PWD/../Third \
            $$PWD/../Third/spdlog \
            $$PWD/../Third/breakpad \
            $$PWD/../opencv_build/include

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
HEADERS += \
    src/PictureAnalysis.h \
    src/analysis.h \
	src/cpp_wrapped.h \
	src/Wave_Low_Top_Info.h \
    src/analysis_global.h

SOURCES += \
    src/PictureAnalysis.cpp \
	src/Wave_Low_Top_Info.cpp \
    src/analysis.cpp

MOC_DIR=moc/
UI_DIR=moc/
DLLDESTDIR+=../Bin
DESTDIR+=../Lib

win32{
    PRECOMPILED_HEADER+= $$PWD\\..\\Include\\Precomp\\precompile.h
    LIBS+=../Lib/DAO.lib \
          ../Lib/Utilities.lib

    CONFIG(debug, debug|release) {
        LIBS += ../lib/OpenCV/opencv_world340d.lib
    } else {
        LIBS += ../lib/OpenCV/opencv_world340.lib
    }
}
unix {
    target.path = /usr/lib
    INSTALLS += target
}


