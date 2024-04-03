#include <Arduino.h>
#include "CCom.h"
#include "CMasterInstance.h"
#include "Frames/Frames.h"

CMasterInstance::CMasterInstance(CCom &com) : _communcations(com)
{
}

CMasterInstance::~CMasterInstance()
{
}

void CMasterInstance::OnSetup()
{
    _communcations.Setup();
}
void CMasterInstance::HandleLoop()
{
    HandleFrames();
}
void CMasterInstance::HandleFrames()
{
    _communcations.HandleFrames();

   
}

/**
 * @brief Sets the wheel dephasaion value.
 *
 * This function sets the wheel dephasaion value, which represents the difference
 * in speed between wheels expressed as a percentage. The value should be in the
 * range of -50 to 50, where a negative value indicates a decrease in speed for
 * one wheel compared to the other, and a positive value indicates an increase.
 *
 * @param value The wheel dephasaion value to set, ranging from -50 to 50.
 *
 * @note This function sends the dephasaion value as a frame via communication interface.
 *
 * @see SendFrame()
 */
void CMasterInstance::SetWheelsDephase(int8_t value)
{
    _communcations.SendFrame(DephaseFrame{value}, EFramePid::DEPHASE_FRAME);
}

/**
 * @brief Sets the wheel dephasaion value with a timeout.
 *
 * This function sets the wheel dephasaion value, which represents the difference
 * in speed between wheels expressed as a percentage, and also specifies a timeout
 * after which the instruction should expire.
 *
 * @param value The wheel dephasaion value to set, ranging from -50 to 50.
 * @param timeout The timeout value (in milliseconds) after which the instruction should expire.
 *
 * @note This function sends the dephasaion value and timeout as a frame via communication interface.
 *
 * @see SendFrame()
 */
void CMasterInstance::SetWheelsDephaseTimeout(int8_t value, uint16_t timeout)
{
    _communcations.SendFrame(DephaseFrameTimeout{value & 0xFF, (value >> 8) & 0xFF}, EFramePid::DEPHASE_FRAME_TIMEOUT);
}

/**
 * @brief Sets the target RPM (Revolutions Per Minute) for the wheels.
 *
 * This function sets the target speed in RPM for the wheels. The target speed
 * will be acquired at an unknown time.
 *
 * @param rpm The target RPM for the wheels.
 *
 * @note This function sends the target RPM as a frame via the communication interface.
 *
 * @see SendFrame()
 */
void CMasterInstance::SetWheelsTargetRpm(int16_t rpm)
{
    _communcations.SendFrame(WheelsSpeedTargetFrame{rpm}, EFramePid::WHEELS_SPEED_TARGET);
}

/**
 * @brief Sets the target RPM (Revolutions Per Minute) for the wheels with a timeout.
 *
 * This function sets the target speed in RPM for the wheels and specifies a timeout
 * after which the instruction should expire.
 *
 * @param rpm The target RPM for the wheels.
 * @param timeout The timeout value (in milliseconds) after which the instruction should expire.
 *
 * @note This function sends the target RPM and timeout as a frame via the communication interface.
 *
 * @see SendFrame()
 */
void CMasterInstance::SetWheelsTargetRpmTimeout(int16_t rpm, int16_t timeout)
{
    _communcations.SendFrame(WheelsSpeedTargetTimeoutFrame{rpm, timeout}, EFramePid::WHEELS_SPEED_TARGET);
}