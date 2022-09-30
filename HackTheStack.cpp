#include <stdio.h>

#include "SuperStack.h"

#include <stdlib.h>
int main()
    {
    SuperStack stk = {};
    DbgStackCtor(&stk, 10);
    return 0;    
    }