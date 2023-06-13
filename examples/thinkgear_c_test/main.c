#include <stdlib.h>
#include <stdio.h>
#include "thinkgearcpp/ThinkGear.h"
#include "BasicListener.h"
#include "thinkgear_test.h"

#define BUFSIZE 512

int main()
{
    thinkgear_t tg;
    tg_listener_t listener;
    TG_Init(&tg);
    TGListener_Init(&listener);
    BasicListener_Setup(&listener);
    tg.ops->add_listener(&tg, &listener);
    printf("ThinkGear begin test:\n");
    tg.ops->load_buffer(&tg, thinkgear_test, thinkgear_test_len);
    printf("ThinkGear end test\n");
    TG_Destroy(&tg);
    TGListener_Destroy(&listener);
    return 0;
     
}
