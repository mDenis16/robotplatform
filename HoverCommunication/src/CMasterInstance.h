#pragma once

class CMasterInstance
{
private:
    /* data */
public:
    CMasterInstance(CCom &com);
    CMasterInstance(/* args */);
    ~CMasterInstance();
    CCom &_communcations;

    void OnSetup();
    void HandleLoop();
    void HandleFrames();

    void SetWheelsDephase(int8_t value);
    void SetWheelsDephaseTimeout(int8_t value, uint16_t timeout);
    void SetWheelsTargetRpm(int16_t rpm);
    void SetWheelsTargetRpmTimeout(int16_t rpm, int16_t timeout);
};
