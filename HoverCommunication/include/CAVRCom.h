#pragma once
enum class EControlMode;

class CAVRCom : public CCom
{
public:
    CAVRCom(EControlMode controlMode);
    HardwareSerial *_serial;

    void writeByte(uint8_t byte) override;
    void writeBytes(uint8_t* buff, size_t length) override;
    uint16_t readBytes(uint8_t *buffer, size_t length) override;    
    uint8_t readByte() override;

    bool find(uint8_t value) override;
    int16_t available() override;
    
    void Setup() override;
};