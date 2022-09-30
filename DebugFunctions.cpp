
#include "DebugFunctions.h"
#include "SuperStack.h"

unsigned MedComissionSS (SuperStack* soldat)
    {
    unsigned flag_error = 0;

    if (soldat == NULL)
        return (flag_error |= NULL_STK_PTR_ERR);

    if (soldat->status != INITIALIZED)
        flag_error |= WRONG_STK_STATUS;
    
    if (soldat->heap == NULL)
        flag_error |= NULL_STK_HEAP;
    
    //if (soldat->capacity > 0)
      //  flag_error |= WRONG_STK_CAPACITY;
    
    if (soldat->top < -1)
        flag_error |= WRONG_STK_TOP;
    
    if (soldat->opening_canary != _OPENING_CANARY_)
        flag_error |= DEAD_STACKOPENING_CANARY;
    
    if (soldat->closing_canary != _CLOSING_CANARY_)
        flag_error |= DEAD_STACKCLOSING_CANARY;

    if (soldat->heap != NULL)
        {
        CANARY* check_opening = (CANARY*) ((char*)soldat->heap - _CANARY_SIZE_);
        CANARY* check_closing = (CANARY*) (soldat->heap + soldat->capacity);
        
        if (*check_opening != _OPENING_CANARY_)
            flag_error |= DEAD_HEAPOPENING_CANARY;
        
        if (*check_closing != _CLOSING_CANARY_)
            flag_error |= DEAD_HEAPCLOSING_CANARY;
        
        //printf("%0x, %0x, soldat = %p, capacity = %d\n", *check_opening, *check_closing, soldat, soldat->capacity);
        }

    //check hash
    printf("%u I Am MEDcomission\n", flag_error);
    return flag_error;
    }

void fprintf_element_t(FILE* file, element_t* ptr)
    {
    if (file == NULL) return;
    if (ptr  == NULL) return;

    if (IsPoison(ptr) == 1)
        fprintf(file, " POISON ");
    else
         fprint_element_type(file, ptr);
    }

void FillPoisonHeap  (element_t* heap, size_t size)
    {
    if (heap == NULL) return;
    if (size < 1)     return;

    for (size_t i = 0; i < size; i++)
        FillPoison (heap + i);
    }

void FillPoison(int* element)
    {
    if (element == NULL) return;
    *element = IntPoison;
    }
    
void FillPoison(char* element)
    {
    if (element == NULL) return;
    *element = CharPoison;
    }

void FillPoison(double* element)
    {
    if (element == NULL) return;
    *element = DoublePoison;
    }

int IsPoison (const int*    element)
    {
    if (element  == NULL)      return 0;
    if (*element == IntPoison) return 1;

    return -1;
    }

int IsPoison (const char*   element)
    {
    if (element  == NULL)       return 0;
    if (*element == CharPoison) return 1;

    return -1;
    }

int IsPoison (const double* element)
    {
    if (element  == NULL)         return 0;
    if (*element == DoublePoison) return 1;

    return -1;
    }


void fprint_element_type(FILE* file, int* element)
    {
    if (file    == NULL) return;
    if (element == NULL) return;

    fprintf(file, " %d ", *element);
    }

void fprint_element_type(FILE* file, char* element)
    {
    if (file    == NULL) return;
    if (element == NULL) return;

    fprintf(file, " %c ", *element);
    }

void fprint_element_type(FILE* file, double* element)
    {
    if (file    == NULL) return;
    if (element == NULL) return;

    fprintf(file, " %lg ", *element);
    }