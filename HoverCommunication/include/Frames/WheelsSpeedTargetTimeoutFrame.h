#pragma once
#include "WheelsSpeedTargetFrame.h"
struct WheelsSpeedTargetTimeoutFrame 
{
    int16_t value;
    uint16_t timeout; // in miliseconds
}__attribute__((__packed__));

