#include "mainwindow.h"
#include <QApplication>
#include <QResource>
#include <QFile>
#include <QDir>
#include <QSettings>
#include <QDebug>
#include <QMessageBox>
#include <QStyleFactory>
#include <QDateTime>
#include "QtSingleApplication"
#include "../Include/Database/Database.h"
#include "../Include/Utilities/log.h"
#include "../Include/Instrument/Instrument.h"
#include "src/comm/GlobalData.h"
#include "src/main/subDialog/MyMessageBox.h"
#include <iostream>
#include <QProcess>
using namespace std;

void initFileLog(const QString& exe_path)
{
    auto log_path = exe_path + "/log/"+QDateTime::currentDateTime().toString("yyyyMMdd");
    QDir dir(log_path);
    if (!dir.exists())
        dir.mkpath(log_path);
    bool on=true;//打开日志
    auto level = on ? SPDLOG_LEVEL_TRACE : SPDLOG_LEVEL_ERROR;
    auto log_file = log_path + "/spdlog.log";
    Log::setup(log_file.toLocal8Bit().data(), level);

    auto instrument_file = log_path;
    Instrument::instance()->initLog(instrument_file,level);
}

int main(int argc, char *argv[])
{
    qSetMessagePattern("[%{time yyyyMMdd h:mm:ss.zzz} %{if-debug}D%{endif}%{if-info}I%{endif}%{if-warning}W%{endif}%{if-critical}C%{endif}%{if-fatal}F%{endif}] %{file}:%{line} - %{message}");
    QtSingleApplication a(argc, argv);
    if (Database::connectDatabase() < 0)
    {
        QMessageBox::information(nullptr, "tip", QObject::tr("database not connect"), QObject::tr("OK"));
        return 0;
    }

    auto exe_path = QCoreApplication::applicationDirPath();
    GlobalData::setExePath(exe_path);
    initFileLog(exe_path);
    QString rccPath(qApp->applicationDirPath() + "/default.rcc");//default
    QResource::registerResource(rccPath);

    QFile file(":normal.qss");
    if (file.open(QFile::ReadOnly)) {
        QString str = file.readAll();
        qApp->setStyleSheet(str);
    } else {
        return 0;
    }

    if (a.isRunning()) {
        a.sendMessage("raise_window_noop", 4000);
        return EXIT_SUCCESS;
    }
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    //QEvent *evt = new QEvent(QEvent::Close);
    MainWindow w;
    a.setActivationWindow(&w);
    a.installNativeEventFilter(&w);
    w.show();
    int exeReturn = a.exec();
    QResource::unregisterResource(rccPath);

    QObject::connect(&a, &QApplication::aboutToQuit, []() {
        qDebug() << "应用程序即将退出";
        Instrument::instance()->closeSocket();
        // 在这里执行你的清理操作
    });


    return exeReturn;
}
