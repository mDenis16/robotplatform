

enum class EFrameType : uint8_t
{
    SET_TARGET_WHEELS_RPM = 0x1,
    SET_TARGET_ANGLE = 0x2,
    SET_WHEEL_OOP = 0x3
};

/*template <typename T>
class CComFrame
{
public:
    uint8_t byteStart = frame_header;
    uint8_t frameSize = sizeof(T);
    T frameContent;
    uint8_t byteEd = frame_end;
};*/
