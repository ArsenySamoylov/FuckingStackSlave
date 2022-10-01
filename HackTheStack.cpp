#include <stdio.h>
#include <stdlib.h>
#define LOGNAME "SOSi.txt"
#include "SuperStack.h"

int main()
    {
    SuperStack stk_ARs = {};

    StackCtor(&stk_ARs, 2);
    printf("\n%p\n", (void*)(((CANARY*)stk_ARs.heap)[-1]));
    printf("%p\n", (void*)((CANARY*)(stk_ARs.heap +stk_ARs.capacity)[0]));
    
    //SSdump (&stk_ARs, 0x1 << 2, init_inf(stk), __func__);
    //fuckDump(&stk_ARs);

    for (int i = 0; i < 3; ++i)
    {
        printf("===========\n");
        StackPush(&stk_ARs, i);

    //    SSdump(&stk_ARs, 0x1 << 2, init_inf(stk), __func__);
        fuckDump(&stk_ARs);
        printf("%d\n%p\n", i, (void*)(((CANARY*)stk_ARs.heap)[-1]));
        printf("%p\n", (void*)((CANARY*)(stk_ARs.heap + stk_ARs.capacity)[0]));
    }

    for (int i = 0; i < 3; ++i)
    {
        StackPop(&stk_ARs);

        //SSdump(&stk_ARs, 0x1 << 2, init_inf(stk), __func__);
        fuckDump(&stk_ARs);
        printf("\n%p\n", (void*)(((CANARY*)stk_ARs.heap)[-1]));
        printf("%p\n", (void*)((CANARY*)(stk_ARs.heap + stk_ARs.capacity)[0]));
    }

    StackDtor(&stk_ARs);

    //SSdump(&stk_ARs, 0x1 << 2, init_inf(stk), __func__);
    fuckDump(&stk_ARs);
    //printf("\n%p\n", (void*)(((CANARY*)stk_ARs.heap)[-1]));
    //printf("%p\n", (void*)((CANARY*)(stk_ARs.heap + stk_ARs.capacity)[0]));

    return 0;    
    }