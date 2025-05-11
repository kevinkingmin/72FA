#-------------------------------------------------
#
# Project created by QtCreator 2020-08-21T16:56:21
#
#-------------------------------------------------

QT       -= gui

#CONFIG(debug, debug|release){
#   TARGET = Modeld
#} else {
#   TARGET = Model
#}
TARGET = Model
TEMPLATE = lib

DEFINES += MODEL_LIBRARY

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
        src/baseSet/CommonType.cpp \
        src/baseSet/InstrumentParasSetModel.cpp \
        src/baseSet/InstrumentStateModel.cpp \
        src/baseSet/AgeUnitModel.cpp \
        src/baseSet/BedNoModel.cpp \
        src/baseSet/DepartmentModel.cpp \
        src/baseSet/DiagnosisModel.cpp \
        src/baseSet/ItemModel.cpp \
        src/baseSet/ProcessModel.cpp \
        src/baseSet/ProcessParaModel.cpp \
        src/baseSet/ProcessStepModel.cpp \
        src/baseSet/RemarkModel.cpp \
        src/baseSet/SampleSenderModel.cpp \
        src/baseSet/SexModel.cpp \
        src/baseSet/SystemSetModel.cpp \
        src/baseSet/TestPaperModel.cpp \
        src/baseSet/WardModel.cpp \
        src/reagent/ProcessReagentModel.cpp \
        src/reagent/ReagentModel.cpp \
        src/result/JudgeRules.cpp \
        src/result/TestResultModel.cpp \
        src/sample/SampleModel.cpp \
        src/sample/SampleRackModel.cpp \
        src/sample/SampleSchModel.cpp \
        src/sample/SampleTestModel.cpp \
        src/sample/TestParasModel.cpp \
        src/sample/BatchAddSampleModel.cpp \
        src/user/UserGroupModel.cpp \
        src/user/UserModel.cpp

HEADERS += \
        src/Model.h \
        src/baseSet/CommonType.h \
        src/baseSet/InstrumentParasSetModel.h \
        src/baseSet/InstrumentStateModel.h \
        src/baseSet/AgeUnitModel.h \
        src/baseSet/BedNoModel.h \
        src/baseSet/DepartmentModel.h \
        src/baseSet/DiagnosisModel.h \
        src/baseSet/ItemModel.h \
        src/baseSet/ProcessModel.h \
        src/baseSet/ProcessParaModel.h \
        src/baseSet/ProcessStepModel.h \
        src/baseSet/RemarkModel.h \
        src/baseSet/SampleSenderModel.h \
        src/baseSet/SexModel.h \
        src/baseSet/SystemSetModel.h \
        src/baseSet/TestPaperModel.h \
        src/baseSet/WardModel.h \
        src/reagent/ProcessReagentModel.h \
        src/reagent/ReagentModel.h \
        src/result/JudgeRules.h \
        src/result/TestResultModel.h \
        src/sample/SampleModel.h \
        src/sample/SampleRackModel.h \
        src/sample/SampleSchModel.h \
        src/sample/SampleTestModel.h \
        src/sample/TestParasModel.h \
        src/sample/BatchAddSampleModel.h \
        src/user/UserGroupModel.h \
        src/user/UserModel.h

win32{
    MOC_DIR=moc/
    UI_DIR=moc/
    DLLDESTDIR+=../Bin
    DESTDIR+=../Lib

    PRECOMPILED_HEADER+=../Include/Precomp/precompile.h

    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\model.h\" \
        \"$$PWD\\..\\Include\\Model\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\baseSet\\*.h\" \
        \"$$PWD\\..\\Include\\Model\\baseSet\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\sample\\*.h\" \
        \"$$PWD\\..\\Include\\Model\\sample\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\user\\*.h\" \
        \"$$PWD\\..\\Include\\Model\\user\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\reagent\\*.h\" \
        \"$$PWD\\..\\Include\\Model\\reagent\\\" /y &
    QMAKE_POST_LINK += xcopy \"$$PWD\\src\\result\\*.h\" \
        \"$$PWD\\..\\Include\\Model\\result\\\" /y &


#    LIBS+=../Lib/SPDLog.lib
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
