#include <Arduino.h>
#include "CCom.h"
#include "CSlaveInstance.h"
#include "Frames/Frames.h"

CSlaveInstance::CSlaveInstance(CCom &com) : _communcations(com)
{
}

void CSlaveInstance::OnSetup()
{
    Serial.println("CSlaveInstance::OnSetup called");
    _communcations.Setup();
}
void CSlaveInstance::HandleLoop()
{
    HandleFrames();
}
void CSlaveInstance::HandleFrames()
{
    _communcations.HandleFrames();
    EFramePid pid = EFramePid::MIN;
    uint8_t *buff = nullptr;
     if (_communcations.PullLatestFrame(buff, pid))
    {
        Serial.println("got speed: ");
        auto merge = (WheelsSpeedTargetFrame *)(buff);

        Serial.println(merge->speed);
    }
}