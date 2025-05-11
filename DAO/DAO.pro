#-------------------------------------------------
#
# Project created by QtCreator 2020-08-21T17:05:58
#
#-------------------------------------------------

QT       += sql
QT       -= gui

TARGET = DAO
TEMPLATE = lib

DEFINES += DAO_LIBRARY

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
        src/Analysis/AnalysisDao.cpp \
        src/Analysis/AnalysisUIDao.cpp \
        src/Reagent/ProcessReagentDao.cpp \
        src/Reagent/ReagentDao.cpp \
        src/aes/aes.cpp \
        src/aes/aesencryptor.cpp \
        src/baseSet/AgeUnitDao.cpp \
        src/baseSet/BedNoDao.cpp \
        src/baseSet/DepartmentDao.cpp \
        src/baseSet/DiagnosisDao.cpp \
        src/baseSet/InstrumentParasSetDao.cpp \
        src/baseSet/ItemDao.cpp \
        src/baseSet/ProcessDao.cpp \
        src/baseSet/ProcessParaDao.cpp \
        src/baseSet/ProcessStepDao.cpp \
        src/baseSet/RemarkDao.cpp \
        src/baseSet/SampleSenderDao.cpp \
        src/baseSet/SexDao.cpp \
        src/baseSet/SystemSetDao.cpp \
        src/baseSet/TestPaperDao.cpp \
        src/baseSet/WardDao.cpp \
        src/dao.cpp \
        src/sample/SampleDao.cpp \
        src/sample/SampleTestDao.cpp \
        src/user/UserDao.cpp \
        src/user/UserGroupDao.cpp

HEADERS += \
        src/Analysis/AnalysisDao.h \
        src/Analysis/AnalysisUIDao.h \
        src/Reagent/ProcessReagentDao.h \
        src/Reagent/ReagentDao.h \
        src/aes/aes.h \
        src/aes/aesencryptor.h \
        src/baseSet/AgeUnitDao.h \
        src/baseSet/BedNoDao.h \
        src/baseSet/DepartmentDao.h \
        src/baseSet/DiagnosisDao.h \
        src/baseSet/InstrumentParasSetDao.h \
        src/baseSet/ItemDao.h \
        src/baseSet/ProcessDao.h \
        src/baseSet/ProcessParaDao.h \
        src/baseSet/ProcessStepDao.h \
        src/baseSet/RemarkDao.h \
        src/baseSet/SampleSenderDao.h \
        src/baseSet/SexDao.h \
        src/baseSet/SystemSetDao.h \
        src/baseSet/TestPaperDao.h \
        src/baseSet/WardDao.h \
        src/dao.h \
        src/sample/SampleDao.h \
        src/sample/SampleTestDao.h \
        src/user/UserDao.h \
        src/user/UserGroupDao.h

DLLDESTDIR+=../Bin
DESTDIR+=../Lib
MOC_DIR=moc/
UI_DIR=moc/

win32{    
    PRECOMPILED_HEADER+=../Include/Precomp/precompile.h
    LIBS+=  ../Lib/Model.lib \
            ../Lib/Utilities.lib
    CONFIG(release, debug|release) {
        LIBS += ../Lib/Database.lib
    } else {
        LIBS += ../Lib/Databased.lib
    }

    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\dao.h\" \
        \"$$PWD\\..\\Include\\DAO\\\" /y &

    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\baseSet\\*.h\" \
        \"$$PWD\\..\\Include\\DAO\\baseSet\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\sample\\*.h\" \
        \"$$PWD\\..\\Include\\DAO\\sample\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\user\\*.h\" \
        \"$$PWD\\..\\Include\\DAO\\user\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\reagent\\*.h\" \
        \"$$PWD\\..\\Include\\DAO\\reagent\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\Analysis\\*.h\" \
        \"$$PWD\\..\\Include\\DAO\\Analysis\\\" /y &
}


unix {
    target.path = /usr/lib
    INSTALLS += target
}


QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

