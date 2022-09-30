#include "my_log.h"

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
