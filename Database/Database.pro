#-------------------------------------------------
#
# Project created by QtCreator 2017-01-20T11:09:17
#
#-------------------------------------------------

QT       += sql

QT       -= gui
CONFIG(release, debug|release){ TARGET = Database}
else{TARGET = Databased}
#TARGET = Database
TEMPLATE = lib

DEFINES += DATABASE_LIBRARY

SOURCES += \
    SourceCode/Database/DatabaseFactory.cpp \
    SourceCode/Interface/Database.cpp

HEADERS += \
    SourceCode/Database/DatabaseFactory.h \
    SourceCode/Interface/Database.h

DESTDIR+=../Lib
DLLDESTDIR+=../Bin
MOC_DIR=moc/
UI_DIR=moc/

win32{
    PRECOMPILED_HEADER+=../Include/Precomp/precompile.h

    #LIBS+=  ../Lib/Utilities.lib

    QMAKE_POST_LINK += xcopy \"$$_PRO_FILE_PWD_\\SourceCode\\Interface\\Database.h\" \
        \"$$_PRO_FILE_PWD_\\..\\Include\\Database\\\" /y &
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
