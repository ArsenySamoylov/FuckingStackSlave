#ifndef MY_LOG // turn off buferization? (mb add modes)
#define MY_LOG

#include <stdlib.h>
#include <stdio.h>

#pragma once

//! @note if you want to change log file name
//!          than define LOGNAME with name before including this file
//! @note if you want to show logs in console
//!          than define LOGNAME without name
#ifndef LOGNAME
#define LOGNAME "StdLogFile.txt"
#endif

//#include "my_colors.h"
FILE* OpenLog  (const char* log_name);
void  CloseLog ();
FILE* GetLog   ();

extern FILE* my_log;

struct SrcLocationInfo
    {
    const char* var_name;
    const char* src_file;
    const char* src_function;
    int         src_line;
    };

#define init_inf(name) ((SrcLocationInfo){#name, __FILE__, __func__, __LINE__}) 
#define  src_loc(name) ((SrcLocationInfo){#name, __FILE__, __func__, __LINE__})

#define $ printf("I AM WORKING IN FUNCTION: %s, in line: %d\n", __func__, __LINE__); //add colors

//! @todo print all given parametrs (add later)
#define $$(...)

#endif