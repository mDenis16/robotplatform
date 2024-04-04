#pragma once

class CSlave
{
public:
    CSlave(CCom &com);
    void OnSetup();
    void HandleLoop();
    void HandleFrames();
    void SpeedKeeper();
    void OnSpeedUpdate(WheelsSpeedTargetFrame* newSpeed);
    void SendHoverSpeedFrame();
    unsigned long speedKeeperTime = 0;
    unsigned long speedKeeperDelayMS = 15;
private:
    int16_t previousTargetSpeed = 0;
    int16_t currentTargetSpeed = 0;
    CCom &_communcations;

    static constexpr int16_t maxSpeedDiff = 150;
};
