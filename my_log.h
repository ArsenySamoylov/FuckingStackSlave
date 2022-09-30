#ifndef NDEBUG
#ifndef MY_LOG // turn off buferization? (mb add modes)
#define MY_LOG

#include <stdlib.h>
#include <stdio.h>

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

FILE* my_log = OpenLog(LOGNAME);

FILE* GetLog()
    {
    return my_log;
    }

FILE* OpenLog(const char* log_name)
    {
    FILE* file = fopen(log_name, "w");

    atexit(CloseLog);

    return (file == NULL) ? stdin : file;   
    }

void CloseLog()
    {
    fputs("\n****************************************************", my_log);
    fputs("\n                Log Successfuly ended               ", my_log);
    fputs("\n****************************************************", my_log);
    if (my_log != stdin)
        fclose(my_log);
    }

struct SrcLocationInfo
    {
    const char* var_name;
    const char* src_file;
    const char* src_function;
    int         src_line;
    };

//(NameStruct){1, 2, ,3 ,4};
#define init_inf(name) ((SrcLocationInfo){#name, __FILE__, __func__, __LINE__}) 
#define  src_loc(name) ((SrcLocationInfo){#name, __FILE__, __func__, __LINE__})

#define $ printf("I AM WORKING IN FUNCTION: %s, in line: %d\n", __func__, __LINE__); //add colors

//! @todo print all given parametrs (add later)
#define $$(...)

#endif
#endif