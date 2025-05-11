#-------------------------------------------------
#
# Project created by QtCreator 2013-04-04T23:11:38
#
#-------------------------------------------------

QT       += gui-private widgets

CONFIG += plugin

TARGET = Qt5SoftKeyboard
TEMPLATE = lib

DEFINES += VIRTUALKEYBOARD_LIBRARY

CONFIG(debug, debug|release){
    LIBS += $$PWD/pinyin/googlepinyind.lib
} else {
    LIBS += $$PWD/pinyin/googlepinyin.lib
}
INCLUDEPATH += $$PWD/pinyin
DEPENDPATH += $$PWD/pinyin

SOURCES += \
    inputcontext.cpp \
    platforminputcontextplugin.cpp \
    googlepinyin.cpp \
    keyboardform.cpp \
    keyeventdispatcher.cpp \
    keyboardformnum.cpp


HEADERS +=\
    pinyinime.h \
    inputcontext.h \
    platforminputcontextplugin.h \
    virtualkeyboard_global.h \
    googlepinyin.h \
    keyboardform.h \
    keyeventdispatcher.h \
    keyboardformnum.h

RESOURCES += \
    res.qrc

DISTFILES += \
    Qt5Input.json
