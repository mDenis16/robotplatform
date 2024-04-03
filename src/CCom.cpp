#include <Arduino.h>
#include "CComFrame.h"

#include "Frames/Frames.h"

#include "CCom.h"
#include "CAVRCom.h"

void CCom::OnFrameReceive(uint8_t *buffer, EFramePid pid)
{
    currentFrameBuffer = buffer;
    _currentFramePid = pid;
}
bool CCom::PullLatestFrame(uint8_t *frameBuffer, EFramePid &pid)
{
    Serial.print("pulled frame pid ");
    Serial.println((uint8_t)_currentFramePid);

    if (_currentFramePid < EFramePid::MIN || _currentFramePid > EFramePid::MAX)
        return false;

    frameBuffer = currentFrameBuffer;
    pid = _currentFramePid;

    return true;
}
void CCom::HandleFrames()
{
    auto bufferSize = available();

    static int index = 0;
    static EFramePid currentFramePID = EFramePid::MIN;
    static uint8_t currentContentIndex = 0;

    while (bufferSize > 0)
    {
        uint8_t currentByte = readByte();

        if (currentByte == frame_start && !(_stateFlags & EFrameStateFlags::WAITING_TO_COMPLETE))
        {
            index = 0;
            _stateFlags |= EFrameStateFlags::WAITING_TO_COMPLETE;
        }
        else if (currentByte == frame_end && (_stateFlags & EFrameStateFlags::GOT_PID_FOR_FRAME))
        {

            if (currentFramePID > EFramePid::MIN && currentFramePID < EFramePid::MAX && index == GetCorrectFrameSize(currentFramePID))
            {
                if (_stateFlags & EFrameStateFlags::WAITING_TO_COMPLETE)
                    _stateFlags &= ~EFrameStateFlags::WAITING_TO_COMPLETE;

                _stateFlags = 0;
                index = 0;
                OnFrameReceive((uint8_t *)(((uintptr_t)(&buffer) + 2)), currentFramePID); // SKIP TWO FIRST BYTES(START, PID)
                break;
            }
            else
            {
                // mismatched size
                index = 0;
                currentFramePID = EFramePid::MIN;
                break;
            }
        }
        else
        {
            if (_stateFlags & EFrameStateFlags::WAITING_TO_COMPLETE)
            {
                if (!(_stateFlags & EFrameStateFlags::GOT_PID_FOR_FRAME))
                {
                    currentFramePID = (EFramePid)(currentByte);
                    _stateFlags |= EFrameStateFlags::GOT_PID_FOR_FRAME;
                }
                else
                {
                    Serial.print("Filled buffer with ");
                    Serial.print((uint8_t)currentByte);
                    Serial.print(" at index ");
                    Serial.println(index);
                    buffer[index++] = currentByte;
                }
            }
        }

        bufferSize--;
    }
}