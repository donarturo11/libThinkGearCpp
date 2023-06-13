#ifndef THINKGEARMESSAGES_H
#define THINKGEARMESSAGES_H
#include "thinkgearcpp/ThinkGear.h"
#include <string>
//struct TG_AsicEegData;
class ThinkGearMessages
{
public:
    ThinkGearMessages();
    ~ThinkGearMessages();
    void displayValue(std::string name, int value);
    void displayEeg(TG_AsicEegData values);
};

#endif // THINKGEARMESSAGES_H
