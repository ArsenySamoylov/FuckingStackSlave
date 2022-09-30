#include <math.h>

#include "SuperStack.h"
#include "DebugFunctions.h"

#define fprintf_stars fprintf(dump_log, "****************************************************\n")
#define dump_log_printf(...) fprintf(dump_log, __VA_ARGS__)

const char* MedComissionErorrMessage[] =
    {
    "Stak pointer has NULL value\n",
    "Stak heap pointer has NULL value\n",
    "Wrong Stack status\n",
    "Wrong Stack capacity\n",
    "Wrong Stack top\n",
    "Opening StackCanary has died\n",
    "Closing StackCanary has died\n",
    "Opening HeapCanary has died\n",
    "Closing HeapCanary has died\n",    
    };

void SSdump(SuperStack* stk_ptr, unsigned flag_error, SrcLocationInfo src, const char* func)
    {
    FILE *dump_log = GetLog();
    if (dump_log == NULL)
        {
        printf("Log file pointer has NULL value\n");
        return;
        }

    fprintf_stars;

    dump_log_printf( "SSdump activated from: \n\n");
    if (func != NULL)
        dump_log_printf( "function = %s\n", func);
    else
        dump_log_printf( "NULL\n");

    dump_log_printf( "Which called from: \n");

    if (src.src_file != NULL)
        dump_log_printf( "\tsource file = %s, \n", src.src_file);
    else
        dump_log_printf( "\tsource file = NULL, \n"); 

    if (src.src_function != NULL)
        dump_log_printf( "\tsource function = %s, ", src.src_function);
    else
        dump_log_printf( "\tsource function = NULL, "); 

    dump_log_printf( "source line = %d,\n", src.src_line);

    if (src.var_name != NULL)
        dump_log_printf( "\tvariable nickname = %s.\n", src.var_name);
    else
        dump_log_printf( "\tvariable nickname = NULL, \n");

    if (stk_ptr == NULL)
        {
        dump_log_printf( "Error occured, given pointer to stack is invalid (Sad Meow)\n");
        dump_log_printf( "\n                   END OF SSDUMP               \n");
        fprintf_stars;
        dump_log_printf( "\n\n");
        return;
        }

    if (flag_error != 0)
        {
        fprintf_stars;
        dump_log_printf( "\n");
        }

    for (int i = 0, error_bytes = sizeof(flag_error) * 8; i < error_bytes;i++ )
        {
        if ( (flag_error & (0x1 << i)) != 0)
            {
            dump_log_printf( "Medcomission found error (error code %d) in stack: \n\t%s\n",
                              i, MedComissionErorrMessage[i]);
            }
        }

    fprintf_stars;

    dump_log_printf( "Stack initialization information: \n\n");
    if ( (stk_ptr->init_inf).var_name != NULL )
        dump_log_printf( "initialization name = %s, ", (stk_ptr->init_inf).var_name);
    else
        {
        dump_log_printf( "initialization name = NULL, ");
        (stk_ptr->init_inf).var_name = "!NO_NAME";
        }

    if ((stk_ptr->init_inf).src_file != NULL)
        dump_log_printf( "initialization file = %s, \n", (stk_ptr->init_inf).src_file);
    else
        dump_log_printf( "initialization file = NULL, \n"); 

    if ((stk_ptr->init_inf).src_function != NULL)
        dump_log_printf( "initialization function = %s, ", (stk_ptr->init_inf).src_function);
    else
        dump_log_printf( "initialization function = NULL,"); 

    dump_log_printf( "initialization line = %d.\n", (stk_ptr->init_inf).src_line);

    fprintf_stars;

    dump_log_printf( "Stack structure information: \n\n");
    dump_log_printf( "%s[%d] - stack name and top\n", (stk_ptr->init_inf).var_name, stk_ptr->top);
    dump_log_printf( "%d - capacity\n", stk_ptr->capacity);
    if (stk_ptr->heap != NULL)
        dump_log_printf( "%p - heap adress.\n", stk_ptr->heap);
    else
        dump_log_printf( "NULL - heap adrees.\n");
    
    fprintf_stars;

    dump_log_printf( "Canary and hash status\n\n");
    //add canary and hash status
    
    fprintf_stars;

    if (stk_ptr->heap == NULL)
        {
        dump_log_printf( "Heap pointer is invalid, therefore no Stack data ;(\n");
        dump_log_printf( "\n                   END OF SSDUMP               \n");
        fprintf_stars;
        dump_log_printf( "\n\n");
        return;
        }
    dump_log_printf( "Stack data: \n\n");
    #ifdef SSDUMP_ALL
        size_t size = stk_ptr->capacity;
        size_t top  = stk_ptr->top;
    #else
        size_t  size =  stk_ptr->top + 1;
    #endif
    
    for (size_t i = 0; i < size; i++)
        {
        dump_log_printf( "%s[%d] = ", (stk_ptr->init_inf).var_name, i);
        #ifdef SSDUMP_ALL
        if (i <=  top)
            fprint_element_type (dump_log, stk_ptr->heap + i);
        else
            fprintf_element_t (dump_log, stk_ptr->heap + i);
        #else
        fprintf_element_type (dump_log, heap + i);
        #endif

        dump_log_printf( "\n");
        }
    
    dump_log_printf( "\n                   END OF SSDUMP               \n");
    fprintf_stars;
    dump_log_printf( "\n\n");
    }

#undef fprintf_stars
#undef dump_log_printf
