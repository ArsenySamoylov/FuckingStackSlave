#include <stdlib.h>
#include "my_safety.h"

const int POCZĄTKOWE_PRZESUNIĘCIE_STOSU = 17;

void* canary_calloc(size_t number_of_elements, size_t size_of_element)
    {
    size_t total_size = number_of_elements*size_of_element + 2*_CANARY_SIZE_;

    void* canary_ptr = calloc(1, total_size);

    if (canary_ptr)
        {
        CANARY* open_canary  = (CANARY*)         canary_ptr;//(CANARY *)array[-1]
        CANARY* close_canary = (CANARY*) ((char*)canary_ptr + total_size - _CANARY_SIZE_);

        *open_canary  = _OPENING_CANARY_;
        *close_canary = _CLOSING_CANARY_;

        canary_ptr = (void*) ((char*) canary_ptr +  _CANARY_SIZE_);
        }

    return canary_ptr; 
    }

void* canary_realloc(void* ptr, size_t new_numbers_of_elements, size_t size_of_element)
    {
    if (!ptr)                                 
        return NULL;
    //if (new_numb_of_elements < 0 || size_of_element < 0) return NULL;

    ptr = realloc( (char*)ptr - _CANARY_SIZE_, new_numbers_of_elements*size_of_element + 2*_CANARY_SIZE_);

    if (ptr)
        {
        CANARY* open_canary  = (CANARY*)           ptr;
        CANARY* close_canary = (CANARY*) ( (char*) ptr + new_numbers_of_elements*size_of_element + _CANARY_SIZE_);

        *open_canary  = _OPENING_CANARY_;
        *close_canary = _CLOSING_CANARY_;

        ptr = (void*) ((char*) ptr + _CANARY_SIZE_);
        }

    return ptr;
    }

void canary_free (void* ptr)
    {
    free((char*)ptr - _CANARY_SIZE_);
    }

int generateHash(const void* start, const void* end)
    {
    if (!start || !end)
        return 0;


    int hash = POCZĄTKOWE_PRZESUNIĘCIE_STOSU;

    for (const char* ptr = (const char *)start; ptr != end; ++ptr)
        hash += *ptr << 5 + *ptr + *(char *)start;

    return hash;
    }