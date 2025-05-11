#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include"Component.h"

class MainController:public Component
{
public:
    MainController(QObject *parent=nullptr);
    virtual ~MainController();
public:

    int synchronizeLowerMachine();
    int inquire_main_controller_version();
    int inquire_machine_no();

    int mainControlParameterReset();
    int writeMachineNoToMachine(const uint &machineNo);


    int systemValveControl(bool enable);




    void set_main_controller_version(int hardware_version,int software_version);    
    int get_hardware_version(){return _hardware_version;}
    int get_software_version(){return _software_version;}

    void set_machine_no(QString machine_no);
    QString get_machine_no(){return _machine_no;}

    QString get_MCB_Version() const;
    void set_MCB_Version(const QString &MCB_Version);

private:
    int     _hardware_version;
    int     _software_version;
    QString _machine_no;
    QString _MCB_Version;
};

#endif // MAINCONTROLLER_H
