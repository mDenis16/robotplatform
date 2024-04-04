#pragma once

#define frame_start 0x99
#define frame_end 0x90

enum class EControlMode
{
    RAW_REAL_TIME,
    PROGRAMATIC
};
enum EFrameStateFlags
{
    NO_STATE = (1 << 0),
    NEW_FRAME = (1 << 1),
    CURRENT_FRAME_DISCARDED = (1 << 2),
    LAST_FRAME_DISCARDED = (1 << 3),
    WAITING_TO_COMPLETE = (1 << 4),
    GOT_PID_FOR_FRAME = (1 << 5),
    SUCCESFULLY_READ_LAST_FRAME = (1 << 6)
};


enum class EFramePid : uint8_t;

class CCom
{
public:
    CCom(){};
    CCom(EControlMode controlMode) : _controlMode(controlMode){};
    virtual void Setup();

    void SetWheelsTargetRpm(int16_t rpm);
    void SetWheelsDephase(int8_t value);
    void SetWheelsDephaseTimeout(int8_t value, uint16_t timeout = 1); // in miliseconds
    void SetTargetRotationAngle(float rot);

    void SetWheelsTargetRpmTimeout(int16_t rpm, int16_t timeout = 1);

    void HandleFrames();

    int16_t GetRealWheelTargetRpm();

    virtual void writeBytes(uint8_t* buff, size_t length) = 0;
    virtual void writeByte(uint8_t byte) = 0;
    virtual bool find(uint8_t value) = 0;

    virtual uint8_t readByte() = 0;
    virtual uint16_t readBytes(uint8_t *buffer, size_t length) = 0;
    virtual int16_t available();

    template <class T>
    void SendFrame(T frame, EFramePid framePid)
    {
        writeByte(frame_start);
        writeByte((uint8_t)framePid);
        writeBytes(((uint8_t *)(&frame)), sizeof(T));
       //for (size_t i = 0; i < sizeof(T); i++)
         //   writeByte(((uint8_t *)(&frame))[i]);

        writeByte(frame_end);
    }
    void OnFrameReceive(uint8_t *buffer, EFramePid pid);
    bool PullLatestFrame(uint8_t **frameBuffer, EFramePid &pid);


    EFramePid _currentFramePid = (EFramePid)0;
    EControlMode _controlMode;
    uint32_t _stateFlags;
    uint8_t currentByte = 0;
    uint8_t buffer[128];
    uint8_t *currentFrameBuffer = nullptr;
     uint8_t head = 0; // Index to insert new data
    uint8_t tail = 0; // Index to read data
};
