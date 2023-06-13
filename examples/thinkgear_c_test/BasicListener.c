#include "BasicListener.h"
#include <stdio.h>
void BasicListener_Setup(tg_listener_t *listener)
{
    tg_listener_ops *ops = listener->ops;
    ops->onRaw=BasicListener_onRaw;
    ops->onBattery=BasicListener_onBattery;
    ops->onPoorSignal=BasicListener_onPoorSignal;
    ops->onAttention=BasicListener_onAttention;
    ops->onMeditation=BasicListener_onMeditation;
    ops->onEeg=BasicListener_onEeg;
    ops->onConnecting=BasicListener_onConnecting;
    ops->onReady=BasicListener_onReady;
    ops->onError=BasicListener_onError;
}

void BasicListener_onRaw(void* receiver, short val)
{
    BasicListener_printValue("Raw", val);
}

void BasicListener_onBattery(void* receiver, unsigned char val)
{
    //BasicListener_printValue("Battery", val);
}

void BasicListener_onPoorSignal(void* receiver, unsigned char val)
{
    //printf("Poor signal\n");
    BasicListener_printValue("Poor signal", val);
}

void BasicListener_onAttention(void* receiver, unsigned char val)
{
    BasicListener_printValue("Attention: ", val);
}

void BasicListener_onMeditation(void* receiver, unsigned char val)
{
    BasicListener_printValue("On meditation", val);
}

void BasicListener_onEeg(void* receiver, TG_AsicEegData val)
{
    printf("======= EEG Values: ===========\n");
    BasicListener_printValue("Eeg delta", val.eegDelta);
    BasicListener_printValue("Eeg theta", val.eegTheta);
    BasicListener_printValue("Eeg Low Alpha", val.eegLowAlpha);
    BasicListener_printValue("Eeg High Alpha", val.eegHighAlpha);
    BasicListener_printValue("Eeg Low Beta", val.eegLowBeta);
    BasicListener_printValue("Eeg High Beta", val.eegHighBeta);
    BasicListener_printValue("Eeg Low Gamma", val.eegLowGamma);
    BasicListener_printValue("Eeg Mid Gamma", val.eegMidGamma);
    printf("===============================\n");
}

void BasicListener_onConnecting(void* receiver, unsigned char val)
{
    BasicListener_printValue("Connection ", val);
}

void BasicListener_onReady(void* receiver, unsigned char val)
{

}

void BasicListener_onError(void* receiver, unsigned char code)
{

}

void BasicListener_printValue(const char* name, int value)
{
    printf("%s: %i\n", name, value);
}
