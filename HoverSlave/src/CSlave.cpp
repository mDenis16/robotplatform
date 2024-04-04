#include <Arduino.h>
#include <CCom.h>
#include <Frames/Frames.h>
#include <SoftwareSerial9.h>
#include "CSlave.h"

#define HOVER_RX_PIN 36
#define HOVER_TX_PIN 37

#define HOVER2_RX_PIN 38
#define HOVER2_TX_PIN 39

#define HOVER_BAUDRATE 26300

// Serial9 testHW = Serial9(&Serial1);

SoftwareSerial9 hoverboardSerial(HOVER_RX_PIN, HOVER_TX_PIN);
SoftwareSerial9 hoverboardSerial2(HOVER2_RX_PIN, HOVER2_TX_PIN);
CSlave::CSlave(CCom &com) : _communcations(com)
{
}

void CSlave::OnSetup()
{
    currentTargetSpeed = 100;
    Serial.println("CSlaveInstance::OnSetup called");
    _communcations.Setup();
    hoverboardSerial.begin(26300);
    hoverboardSerial2.begin(26300);
}
void CSlave::HandleLoop()
{
    HandleFrames();
    SpeedKeeper();
}
void CSlave::OnSpeedUpdate(WheelsSpeedTargetFrame *frame)
{
    Serial.print("Updated speed to ");
    Serial.println(frame->speed);
    int16_t speedDiff = abs(frame->speed - currentTargetSpeed);
    if (speedDiff <= maxSpeedDiff && speedDiff > 0)
        currentTargetSpeed = frame->speed;
}

void CSlave::HandleFrames()
{
    _communcations.HandleFrames();
    EFramePid pid = EFramePid::MIN;
    static uint8_t *buff = nullptr;

    if (_communcations.PullLatestFrame(&buff, pid))
    {
        switch (pid)
        {
        case EFramePid::WHEELS_SPEED_TARGET:
        {
            auto frame = (WheelsSpeedTargetFrame *)(buff);
            OnSpeedUpdate(frame);
            break;
        }

        default:
            break;
        }
    }
}

void CSlave::SpeedKeeper()
{
    if (millis() >= speedKeeperTime)
    {
        SendHoverSpeedFrame();
        speedKeeperTime = millis() + speedKeeperDelayMS;
    }
}

void CSlave::SendHoverSpeedFrame()
{
    hoverboardSerial.write9(256);
    hoverboardSerial.write9(currentTargetSpeed & 0xFF);
    hoverboardSerial.write9((currentTargetSpeed >> 8) & 0xFF); // primi 8
    hoverboardSerial.write9(currentTargetSpeed & 0xFF);
    hoverboardSerial.write9((currentTargetSpeed >> 8) & 0xFF); // restu de 8
    hoverboardSerial.write9(85);
    // Serial.println("Sent frame to hover");
    hoverboardSerial2.write9(256);
    hoverboardSerial2.write9(currentTargetSpeed & 0xFF);
    hoverboardSerial2.write9((currentTargetSpeed >> 8) & 0xFF); // primi 8
    hoverboardSerial2.write9(currentTargetSpeed & 0xFF);
    hoverboardSerial2.write9((currentTargetSpeed >> 8) & 0xFF); // restu de 8
    hoverboardSerial2.write9(85);
}