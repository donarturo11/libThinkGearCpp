#include "thinkgearcpp/ThinkGear.h"
#include "ThinkGearMonitor.h"
#include "thinkgear_test.h"
#include <iostream>

int main()
{
    using namespace libThinkGearCpp;
    ThinkGear tg;
    ThinkGearMonitor mon;
    tg.addListener( &mon);
    for (int i=0; i<thinkgear_test_len; i++) {
        tg.load(thinkgear_test[i]);
    }
    return 0;
     
}
