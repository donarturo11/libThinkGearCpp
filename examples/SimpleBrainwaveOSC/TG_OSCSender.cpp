#include "TG_OSCSender.h"
#include <iostream>
namespace TG {
OSCSender::OSCSender(std::string ip_addr, int port, void* socket, SocketCallback socket_callback)
{
    _socket = socket;
    sendToSocket = socket_callback;
}

OSCSender::~OSCSender()
{
 
}

void OSCSender::onThinkGearRaw(short val)
{
    lo::Message msg("i", val);
    sendOSC("/raw", msg);    
}

void OSCSender::onThinkGearBattery(unsigned char val)
{
    
}

void OSCSender::onThinkGearPoorSignal(unsigned char val)
{
    float f_val = (float)(val)/ (float) 200;
    lo::Message msg("i", val);
    sendOSC("/signal", msg);
}

void OSCSender::onThinkGearAttention(unsigned char val)
{
    float f_val = (float) val / (float) 100;
    lo::Message msg("f", f_val);
    sendOSC("/attention", msg);
}

void OSCSender::onThinkGearMeditation(unsigned char val)
{
    float f_val = (float) val/ (float) 100;
    lo::Message msg("f", f_val);
    sendOSC("/meditation", msg);
}

void OSCSender::onThinkGearEeg(eegData val)
{
    const std::string pathes[] = {
        "/eegdelta",
        "/eegtheta",
        "/eeglowalpha",
        "/eeghighalpha",
        "/eeglowbeta",
        "/eeghighbeta",
        "/eeglowgamma",
        "/eeghighgamma"
    };
    
    int sum = val.eegSum;
    int path_idx=0;
    for(unsigned int *it=&(val.eegDelta); it!= &(val.eegMidGamma)+1; it++) {
        float fvalue = ((float)(*it)/(float) (sum) );
        sendEegValue(pathes[path_idx], fvalue);
        path_idx++;
    }
}

void OSCSender::onThinkGearConnecting(unsigned char val)
{

}

void OSCSender::onThinkGearReady(unsigned char val)
{

}

void OSCSender::onThinkGearError(unsigned char val)
{

}


void OSCSender::sendOSC(std::string path, lo::Message& msg)
{
    if (!sendToSocket) return;
    struct {
        size_t size;
        unsigned char data[BUFFERSIZE];
    } buffer;
    
    msg.serialise(path, buffer.data, &(buffer.size));
    sendToSocket(_socket, buffer.data, buffer.size);
}

void OSCSender::sendEegValue(std::string path, float val)
{
    lo::Message msg("f", val);
    sendOSC(path, msg);
}

} //namespace ThinkGear
