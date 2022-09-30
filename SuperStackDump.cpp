#include <math.h>

#include "SuperStack.h"
#include "DebugFunctions.h"

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
        printf("Log file pointer has NULL value\n");\
        return;
        }
    fprintf(dump_log, "****************************************************\n");
    fprintf(dump_log, "SSdump activated from: \n\n");
    if (func != NULL)
        fprintf(dump_log, "function = %s\n", func);
    else
        fprintf(dump_log, "NULL\n");

    fprintf(dump_log, "Which called from: \n");

    if (src.src_file != NULL)
        fprintf(dump_log, "\tsource file = %s, \n", src.src_file);
    else
        fprintf(dump_log, "\tsource file = NULL, \n"); 

    if (src.src_function != NULL)
        fprintf(dump_log, "\tsource function = %s, ", src.src_function);
    else
        fprintf(dump_log, "\tsource function = NULL, "); 

    fprintf(dump_log, "source line = %d,\n", src.src_line);

    if (src.var_name != NULL)
        fprintf(dump_log, "\tvariable nickname = %s.\n", src.var_name);
    else
        fprintf(dump_log, "\tvariable nickname = NULL, \n");

    if (stk_ptr == NULL)
        {
        fprintf(dump_log, "Error occured, given pointer to stack is invalid (Sad Meow)\n");
        return;
        }
    
    for (int i = 0, error_bytes = sizeof(flag_error) * 8; i < error_bytes;i++ )
        {
        if (flag_error & (0x1 << i) != 0)
            {
            fprintf(dump_log, "Medcomission found error (error code %d) in stack: %s",
                    i, MedComissionErorrMessage[i]);
            }
        }

    fprintf(dump_log, "****************************************************\n");
    fprintf(dump_log, "Stack initialization information: \n\n");
    if ( (stk_ptr->init_inf).var_name != NULL )
        fprintf(dump_log, "initialization name = %s, ", (stk_ptr->init_inf).var_name);
    else
        {
        fprintf(dump_log, "initialization name = NULL, ");
        (stk_ptr->init_inf).var_name = "!NO_NAME";
        }

    if ((stk_ptr->init_inf).src_file != NULL)
        fprintf(dump_log, "initialization file = %s, \n", (stk_ptr->init_inf).src_file);
    else
        fprintf(dump_log, "initialization file = NULL, \n"); 

    if ((stk_ptr->init_inf).src_function != NULL)
        fprintf(dump_log, "initialization function = %s, ", (stk_ptr->init_inf).src_function);
    else
        fprintf(dump_log, "initialization function = NULL,"); 

    fprintf(dump_log, "initialization line = %d.\n", (stk_ptr->init_inf).src_line);
    fprintf(dump_log, "****************************************************\n");

    fprintf(dump_log, "Stack structure information: \n\n");
    fprintf(dump_log, "%s[%d] - stack name and top\n", (stk_ptr->init_inf).var_name, stk_ptr->top);
    fprintf(dump_log, "%d - capacity\n", stk_ptr->capacity);
    if (stk_ptr->heap != NULL)
        fprintf(dump_log, "%p - heap adress.\n", stk_ptr->heap);
    else
        fprintf(dump_log, "NULL - heap adrees.\n");
    
    fprintf(dump_log, "****************************************************\n");
    fprintf(dump_log, "Canary and hash status\n\n");
    //add canary and hash
    fprintf(dump_log, "****************************************************\n");

    if (stk_ptr->heap == NULL)
        return;

    fprintf(dump_log, "Stack data: \n\n");
    #ifdef SSDUMP_ALL
        size_t size = stk_ptr->capacity;
        size_t top  = stk_ptr->top;
    #else
        size_t  size =  stk_ptr->top + 1;
    #endif
    
    for (size_t i = 0; i < size; i++)
        {
        fprintf(dump_log, "%s[%d] = ", (stk_ptr->init_inf).var_name, i);
        #ifdef SSDUMP_ALL
        if (i <  top)
            fprint_element_type (dump_log, stk_ptr->heap + i);
        else
            fprintf_element_t (dump_log, stk_ptr->heap + i);
        #else
        fprintf_element_type (dump_log, heap + i);
        #endif

        fprintf(dump_log, "\n");
        }
    
    fprintf(dump_log, "\nEND OF SSDUMP\n");
    fprintf(dump_log, "****************************************************\n");
    }
