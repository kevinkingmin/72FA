#ifndef ENCODER_H
#define ENCODER_H
#include"Component.h"

class Encoder:public Component
{
public:    
    explicit Encoder(EncoderAddress address,QObject *parent=nullptr);
    virtual ~Encoder();
public:
    int inquireParameter();
    int inquireValue();
    int writeParasToEncoder(const uint para);

    EncoderAddress getAddress() const;

    int getPrescale() const;
    void setPrescale(int prescale);

    int getEncoderValue() const;
    void setEncoderValue(int value);

private:
    EncoderAddress _address;
    int _prescale;
    int _encoderValue;
};

#endif // ENCODER_H
