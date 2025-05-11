#-------------------------------------------------
#
# Project created by QtCreator 2020-08-21T17:07:03
#
#-------------------------------------------------

QT       -= gui

TARGET = BLL
TEMPLATE = lib

DEFINES += BLL_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += \
            $$PWD/../Third \
            $$PWD/../Third/spdlog \
            $$PWD/../Third/breakpad

SOURCES += \
        src/baseSet/BedNoBLL.cpp \
        src/baseSet/DepartmentBLL.cpp \
        src/baseSet/DiagnosisBLL.cpp \
        src/baseSet/InstrumentParasSetBLL.cpp \
        src/baseSet/ItemBll.cpp \
        src/baseSet/ProcessBLL.cpp \
        src/baseSet/ProcessParaBLL.cpp \
        src/baseSet/ProcessStepBLL.cpp \
        src/baseSet/RemarkBLL.cpp \
        src/baseSet/SampleSenderBLL.cpp \
        src/baseSet/SexBLL.cpp \
        src/baseSet/SystemSetBLL.cpp \
        src/baseSet/TestPaperBLL.cpp \
        src/baseSet/WardBLL.cpp \
        src/comm/BarCodeRule.cpp \
        src/comm/CliaEncryption.cpp \
        src/comm/GetLanguageClsBLL.cpp \
        src/reagent/ProcessReagentBLL.cpp \
        src/reagent/ReagentBLL.cpp \
        src/sample/SampleBLL.cpp \
        src/user/UserBLL.cpp \
        src/baseSet/AgeUnitBLL.cpp

HEADERS += \
        src/baseSet/BedNoBLL.h \
        src/baseSet/DepartmentBLL.h \
        src/baseSet/DiagnosisBLL.h \
        src/baseSet/InstrumentParasSetBLL.h \
        src/baseSet/ItemBll.h \
        src/baseSet/ProcessBLL.h \
        src/baseSet/ProcessParaBLL.h \
        src/baseSet/ProcessStepBLL.h \
        src/baseSet/RemarkBLL.h \
        src/baseSet/SampleSenderBLL.h \
        src/baseSet/SexBLL.h \
        src/baseSet/SystemSetBLL.h \
        src/baseSet/TestPaperBLL.h \
        src/baseSet/WardBLL.h \
        src/comm/BarCodeRule.h \
        src/comm/CliaEncryption.h \
        src/comm/GetLanguageClsBLL.h \
        src/reagent/ProcessReagentBLL.h \
        src/reagent/ReagentBLL.h \
        src/sample/SampleBLL.h \
        src/user/UserBLL.h \
        src/baseSet/AgeUnitBLL.h \
        src/bll.h

MOC_DIR=moc/
UI_DIR=moc/
DLLDESTDIR+=../Bin
DESTDIR+=../Lib

win32{
    LIBS+=../Lib/Model.lib \
          ../Lib/Utilities.lib \
          ../Lib/DAO.lib

    PRECOMPILED_HEADER+=../Include/Precomp/precompile.h

    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\bll.h\" \
        \"$$PWD\\..\\Include\\BLL\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\baseSet\\*.h\" \
        \"$$PWD\\..\\Include\\BLL\\baseSet\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\sample\\*.h\" \
        \"$$PWD\\..\\Include\\BLL\\sample\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\user\\*.h\" \
        \"$$PWD\\..\\Include\\BLL\\user\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\reagent\\*.h\" \
        \"$$PWD\\..\\Include\\BLL\\reagent\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\comm\\*.h\" \
        \"$$PWD\\..\\Include\\BLL\\comm\\\" /y &
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
