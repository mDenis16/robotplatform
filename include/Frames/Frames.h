#pragma once

#include "DephaseFrame.h"
#include "DephaseFrameTimeout.h"
#include "WheelsSpeedTargetTimeoutFrame.h"
#include "WheelsSpeedTargetFrame.h"

enum class EFramePid : uint8_t
{
    MIN = 0x1,
    DEPHASE_FRAME,
    DEPHASE_FRAME_TIMEOUT,
    WHEELS_SPEED_TARGET,
    WHEELS_SPEED_TARGET_TIMEOUT,
    MAX
};

inline static GetCorrectFrameSize(EFramePid pid)
{
    switch (pid)
    {
    case EFramePid::DEPHASE_FRAME:
        return sizeof(DephaseFrame);
    case EFramePid::DEPHASE_FRAME_TIMEOUT:
        return sizeof(DephaseFrameTimeout);
    case EFramePid::WHEELS_SPEED_TARGET:
        return sizeof(WheelsSpeedTargetFrame);
    case EFramePid::WHEELS_SPEED_TARGET_TIMEOUT:
        return sizeof(WheelsSpeedTargetTimeoutFrame);
    default:
        return 0;
    }
}