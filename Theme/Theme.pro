#-------------------------------------------------
#
# Project created by QtCreator 2020-08-21T15:52:30
#
#-------------------------------------------------

QT       += gui

TARGET = Theme
TEMPLATE = lib

DEFINES += THEME_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src\Theme.cpp

HEADERS += \
        src\Theme.h \
        theme_global.h 

DLLDESTDIR+=../Bin
INCLUDEPATH += ../Include

win32{
    DESTDIR+=../Lib
#    PRECOMPILED_HEADER+=../Include/Precomp/precompile.h
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\theme.h\" \
        \"$$PWD\\..\\Include\\Theme\\\" /y &
 #   QMAKE_POST_LINK += rcc -binary $$PWD/resources.qrc -o $$PWD/Bin/resources.rcc &
}
QMAKE_POST_LINK += rcc -binary $$PWD/resources.qrc \
    -o $$PWD/../Bin/default.rcc &
#D:\liuxing\work\HumaClia2000\HumaClia\Bin
unix {
    target.path = /usr/lib
    INSTALLS += target
}

RC_FILE += $$PWD/logo.rc
RESOURCES += \
    resources.qrc

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

DISTFILES +=
