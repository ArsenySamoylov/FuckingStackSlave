#ifndef MY_SAFETY
#define MY_SAFETY

#include <stdlib.h>

#pragma once

typedef __int64 CANARY;

const int _CANARY_SIZE_ = sizeof(CANARY);

const int _OPENING_CANARY_ = 0xABCDEF;
const int _CLOSING_CANARY_ = 0xFEDCBA;
//hash

void* canary_calloc   (size_t numbers_of_elements, size_t size_of_elemet);
void* canary_realloc  (void* ptr, size_t new_numb_of_elements, size_t size_of_element);
void  canary_free     (void* ptr);

#endif