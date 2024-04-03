#pragma once

class CSlaveInstance
{
public:
    CSlaveInstance(CCom &com);
    void OnSetup();
    void HandleLoop();
    void HandleFrames();
private:
    CCom &_communcations;
};