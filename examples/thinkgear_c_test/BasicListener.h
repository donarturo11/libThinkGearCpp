#ifndef BASICLISTENER_H
#define BASICLISTENER_H
#include <stdlib.h>
#include "thinkgearcpp/ThinkGear.h"
void BasicListener_Setup(tg_listener_t *listener);

void BasicListener_onRaw(void* receiver, short val);
void BasicListener_onBattery(void* receiver, unsigned char val);
void BasicListener_onPoorSignal(void* receiver, unsigned char val);
void BasicListener_onAttention(void* receiver, unsigned char val);
void BasicListener_onMeditation(void* receiver, unsigned char val);
void BasicListener_onEeg(void* receiver, TG_AsicEegData val);
void BasicListener_onConnecting(void* receiver, unsigned char val);
void BasicListener_onReady(void* receiver, unsigned char val);
void BasicListener_onError(void* receiver, unsigned char val);
void BasicListener_printValue(const char* name, int value);

#endif // BASICLISTENER_H
