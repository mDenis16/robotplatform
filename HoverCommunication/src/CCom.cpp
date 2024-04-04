#include <Arduino.h>
#include "CComFrame.h"

#include "Frames/Frames.h"

#include "CCom.h"
#include "CAVRCom.h"

void CCom::OnFrameReceive(uint8_t *buffer, EFramePid pid)
{
    _currentFramePid = pid;
}
bool CCom::PullLatestFrame(uint8_t** frameBuffer, EFramePid &pid)
{
    if (_currentFramePid <= EFramePid::MIN || _currentFramePid >= EFramePid::MAX)
        return false;

    *frameBuffer = (uint8_t*)(&buffer);
    pid = _currentFramePid;

    _currentFramePid= EFramePid::MIN;
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

                OnFrameReceive((uint8_t *)(&buffer), currentFramePID);

            /*    Serial.print("Got ");
                Serial.print(index);
                Serial.println(" bytes");

                for (size_t i = 0; i < index; i++)
                {
                    Serial.println(buffer[i]);
                }

                Serial.println("end");
                    int16_t *val = (int16_t *)(&buffer);
                Serial.println(*val);
                
                */

            
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
                    buffer[index++] = currentByte;
                }
            }
        }

        bufferSize--;
    }
}