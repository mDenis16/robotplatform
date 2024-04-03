#include <Arduino.h>
#include "CCom.h"
#include "CAVRCom.h"

CAVRCom::CAVRCom(EControlMode controlMode) : CCom(controlMode)
{
    _serial = &Serial3;
}

void CAVRCom::Setup()
{
    Serial.println("CAVRCom called");
    _serial->begin(9600, SERIAL_8N1);
}

uint8_t CAVRCom::readByte()
{
    return (uint8_t)_serial->read();
}

uint16_t CAVRCom::readBytes(uint8_t *buffer, size_t length)
{
    return (uint16_t)_serial->readBytes(buffer, length);
}

void CAVRCom::writeByte(uint8_t byte)
{
    _serial->write(byte);
};

bool CAVRCom::find(uint8_t byte)
{
    return _serial->find(byte);
}

int16_t CAVRCom::available()
{
    return _serial->available();
}