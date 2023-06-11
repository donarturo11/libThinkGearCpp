#ifndef THINKGEAR_DEVICE_H
#define THINKGEAR_DEVICE_H
#include <string>
namespace libThinkGearCpp {
class ThinkGearDevice;
typedef std::unique_ptr<ThinkGearDevice> ThinkGearDevicePtr;
class ThinkGearDevice
{
public:
    virtual void setup(std::string portname, int baudrate) = 0;
    virtual void open() = 0;
    virtual void close() = 0;
    virtual int read(char* buffer, int bufferSize) = 0;
    virtual int write(char* buffer, int bufferSize) = 0;
};
}
#endif // THINKGEAR_DEVICE
