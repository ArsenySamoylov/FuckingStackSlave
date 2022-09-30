#include <stdlib.h>
#include "my_log.h"

static FILE* my_log = OpenLog(LOGNAME);

FILE* GetLog()
    {
    return my_log;
    }

FILE* OpenLog(const char* log_name)
    {
    FILE* file = fopen(log_name ? log_name : "", "w");

    if (!file)
        file = stdout;

    atexit(CloseLog);

    return file;//(file == NULL) ? ?????stdin?????? : file;   
    }

void CloseLog()
    {
    fputs("\n****************************************************", my_log);
    fputs("\n                Log Successfuly ended               ", my_log);
    fputs("\n****************************************************", my_log);

    if (my_log && my_log != stdout)
        fclose(my_log);
    }
