#include <stdio.h>

#define LOGNAME "SOSi.txt"

#include "SuperStack.h"

#include <stdlib.h>
int main()
    {
    SuperStack stk_ARs = {};
    StackCtor(&stk_ARs, 10);
    StackPush(&stk_ARs, 49);
    SSdump (&stk_ARs, 0x1 << 2, init_inf(stk), __func__);
    StackDtor(&stk_ARs);
    return 0;    
    }