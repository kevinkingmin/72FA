#include "SampleRackModel.h"

SampleRackModel::SampleRackModel():
    _Rack(0)
  ,_Position(0)
  ,_barcode("")
{
}


int SampleRackModel::getRack() const
{
    return _Rack;
}

void SampleRackModel::setRack(int Rack)
{
    _Rack = Rack;
}

int SampleRackModel::getPosition() const
{
    return _Position;
}

void SampleRackModel::setPosition(int Position)
{
    _Position = Position;
}

QString SampleRackModel::getBarcode() const
{
    return _barcode;
}

void SampleRackModel::setBarcode(const QString &barcode)
{
    _barcode = barcode;
}
