#ifndef TG_OSCSENDER_H
#define TG_OSCSENDER_H
#include "thinkgearcpp/ThinkGear.h"
#include "lo/lo_cpp.h"
#include <string>
#include <memory>

#define BUFFERSIZE 1024

namespace TG {

class OSCSender : public libThinkGearCpp::ThinkGearAbstractListener
{
typedef void (*SocketCallback)(void* socket, unsigned char* data, size_t size);
public:
    OSCSender(std::string ip_addr, int port, void* socket, SocketCallback socket_callback);
    ~OSCSender();
    void onThinkGearRaw(short val);
    void onThinkGearBattery(unsigned char val);
    void onThinkGearPoorSignal(unsigned char val);
    void onThinkGearAttention(unsigned char val);
    void onThinkGearMeditation(unsigned char val);
    void onThinkGearEeg(tg_eegint_t val);
    void onThinkGearConnecting(unsigned char val);
    void onThinkGearReady(unsigned char val);
    void onThinkGearError(unsigned char val);
    void onThinkGearBlinkStrength(unsigned char val) {}
    //void countMax(TG_AsicEegData val);
    SocketCallback sendToSocket;
private:
    void sendOSC(std::string path, lo::Message& msg);
    void sendEegValue(std::string path, float val);
protected:
    uint32_t _max;
    int _bufsize;
    void* _socket;
};
} //namespace ThinkGear
#endif // TG_OSCSENDER_H
