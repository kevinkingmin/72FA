#ifndef SAMPLERACKMODEL_H
#define SAMPLERACKMODEL_H
#include <QString>
#include "../Model.h"

class MODELSHARED_EXPORT SampleRackModel
{
public:
    SampleRackModel();

    int getRack() const;
    void setRack(int Rack);

    int getPosition() const;
    void setPosition(int Position);

    QString getBarcode() const;
    void setBarcode(const QString &barcode);

private:
    int _Rack;
    int _Position;
    QString _barcode;
};

#endif // SAMPLERACKMODEL_H
