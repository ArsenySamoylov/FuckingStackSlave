#include "SuperStack.h"

int SuperStackCtor (SuperStack* stk, size_t capacity
                   ON_SUPERDEBUG(, SrcLocationInfo init_inf) )
    {
    if (stk == NULL)                         return NULL_STK_PTR_CTR;
    //if (capacity < 0)                         return WRONG_CAPACITY;
    if (stk->status != UNINITIALIZED)        return INITIALIZED_STACK;

    stk->capacity = capacity;
    stk->top      = -1;

    if (capacity > 0) 
        stk->heap = (element_t*) canary_calloc (capacity, sizeof (element_t));

    stk->opening_canary = _OPENING_CANARY_;
    stk->closing_canary = _CLOSING_CANARY_;
    #ifndef NDEBUG
    FillPoisonHeap (stk->heap, capacity);

    stk->init_inf = init_inf;
    #endif

    //hash
    //not yet

    //verification 
    verificateSS(stk, init_inf, ERROR_INITIALIZATION);

    return SUCCESS_INITIALIZATION;
    }

void SuperStackDtor (SuperStack* stk
                    ON_SUPERDEBUG(, SrcLocationInfo location) )
    {
    verificateSS(stk, location);
    
    canary_free ((void*) stk->heap);

    stk->status = DEAD; 

    stk->heap   = NULL;
    stk->capacity = 0;
    stk->top = -1; 
    }

void  SSpush (SuperStack* stk, element_t value
              ON_SUPERDEBUG( , SrcLocationInfo  location)  )
    {
    //if (stk == NULL)   return;
    verificateSS(stk, location);
    if (stk->capacity == 0)
        {
        stk->heap     = (element_t*) canary_realloc(stk->heap, _HEAP_MIN_CAPACITY_, _ELEMENT_T_SIZE_);
        stk->capacity = _HEAP_MIN_CAPACITY_;
        }

    if (stk->top + 1 >= stk->capacity)
        {
        stk->heap = (element_t*) canary_realloc(stk->heap, stk->capacity * 2, _ELEMENT_T_SIZE_);
        stk->capacity *= 2;
        }

    (stk->heap)[stk->top] = value;
    (stk->top)++;
    }

 element_t SSpop    (SuperStack* stk
                    ON_SUPERDEBUG( , SrcLocationInfo  location) )
    {
    verificateSS(stk, location, 0);

    if (stk->capacity > 4 * stk->top)
        {
        stk->heap      = (element_t*) canary_realloc(stk->heap, stk->capacity / 2, _ELEMENT_T_SIZE_);
        stk->capacity /= 2;
        }

    if (stk->top == -1)
        return 0;

    return (stk->heap)[(stk->top)--];
    }

element_t SStop   (SuperStack* stk 
                  ON_SUPERDEBUG(, SrcLocationInfo location) )
    {
    verificateSS(stk, location, 0);

    if (stk->top == -1)
        return 0;
        
    return (stk->heap)[(stk->top)];
    }