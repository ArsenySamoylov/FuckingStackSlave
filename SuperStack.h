#ifndef SUPER_DUPER_MEGA_XUEGA_STACK
#define SUPER_DUPER_MEGA_XUEGA_STACK

#ifndef NDEBUG
#define ON_SUPERDEBUG(...) __VA_ARGS__
#else
#define ON_SUPERDEBUG(...)
#endif // NDEBUG

//! @note if you want to change settings than
//!          look up in SuperStackConfig.h
#include "SuperStackConfig.h"
#include "my_safety.h"
#include "my_log.h"
//#include "SuperStackDebugger.h"

enum SuperStackCtorErr
    {
    NULL_STK_PTR_CTR   = -2,
    WRONG_CAPACITY     = -3,
    INITIALIZED_STACK  = -4,

    ERROR_INITIALIZATION   = -1,
    SUCCESS_INITIALIZATION =  1,
    };

//#define GZHA_UNDERSTOOD true //thx Ded

struct SuperStack
    {
    CANARY opening_canary;

    element_t* heap = NULL; // HEAP
    size_t     capacity;
    size_t     top;

    int status = UNINITIALIZED;

    //hash

    #ifndef NDEBUG
    SrcLocationInfo init_inf;
    #endif

    CANARY closing_canary;
    };

//************************************ ptotytypes
static int  SuperStackCtor (SuperStack* stk, size_t capacity
                     ON_SUPERDEBUG( , SrcLocationInfo init_inf)         );

void SuperStackDtor (SuperStack* stk             
                     ON_SUPERDEBUG( , SrcLocationInfo location) );

void      SSpush   (SuperStack* stk, element_t value
                    ON_SUPERDEBUG( , SrcLocationInfo  location)  );

element_t SSpop    (SuperStack* stk
                    ON_SUPERDEBUG( ,  SrcLocationInfo  location) );

element_t SSTop    (); // ded's old jokes: { return ZZTop(); }; 
//************************************ end of protytypes
//************************************ prototypes
unsigned MedComissionSS (SuperStack* prezyvnik); //todo: check if dead
void SSdump (SuperStack* negoden, unsigned flag_err, 
             SrcLocationInfo src_inf, const char* calling_func);
    
void fprintf_element_t(FILE* file, element_t* ptr);
//! @note if you want to use SSDump with unsupported type
//!       than add your own  function
void fprint_element_type(FILE* file, int*    element);
void fprint_element_type(FILE* file, char*   element);
void fprint_element_type(FILE* file, double* element);
    
//void FillPoisonStack (SuperStack* stk);
void FillPoisonHeap  (element_t* heap, size_t size);
//! @note if you want to debug Stack with unsupported type
//!       than add your own FillPoison and IsPoison function
int       IsPoison   (const int*    element);
int       IsPoison   (const char*   element);
int       IsPoison   (const double* element);

void FillPoison (int*    element);
void FillPoison (char*   element);
void FillPoison (double* element);
//************************************ end of prototypes

//************************************ shells
#define DbgStackCtor(stk_ptr, capacity) SuperStackCtor (stk_ptr, capacity     \
                                            ON_SUPERDEBUG(, init_inf(stk_ptr)) );
                                                                                                 

#define DbgStackDtor(stk_ptr)           SuperStackDtor (stk_ptr               \
                                            ON_SUPERDEBUG(, src_loc(stk_ptr)) );
          

#define DbgPush
#define DbgPop
#define DbgTop

#define verificateSS(soldat, SrsLoc, ...)                             \
    unsigned flag_err = MedComissionSS (soldat);                      \
    if (flag_err != 0) { SSdump (soldat, flag_err, SrsLoc, __func__); return __VA_ARGS__; } 

//************************************ end of shells

//************************************ real functions
static int SuperStackCtor (SuperStack* stk, size_t capacity
                   ON_SUPERDEBUG(, SrcLocationInfo init_inf) )
    {
    if (stk == NULL)                          return NULL_STK_PTR_CTR;
    if (capacity < 0)                         return WRONG_CAPACITY;
    if (stk->status != UNINITIALIZED)       return INITIALIZED_STACK;

    stk->capacity = capacity;
    stk->top      = 0;

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

    canary_free ((void*) stk);
    stk->status = DEAD;  
    }

void  SSpush (SuperStack* stk, element_t value
              ON_SUPERDEBUG( , SrcLocationInfo  location)  )
    {
    //if (stk == NULL)   return;
    verificateSS(stk, location);

    }


//************************************ end of functions realisation
#endif

#ifndef SUPERSTACKDEBUGGER
#define SUPERSTACKDEBUGGER

#include <math.h>

//! @note if this macros defined then dump will dump all
//!          all elements from stack
#define SSDUMP_ALL  

unsigned enum MedComissionSS_err
    {
    NULL_STK_PTR_ERR   = 0x1 << 1,
    NULL_STK_HEAP      = 0x1 << 2,
    WRONG_STK_STATUS   = 0x1 << 3,
    WRONG_STK_CAPACITY = 0x1 << 4, 
    WRONG_STK_TOP      = 0x1 << 5,


    };

const char* MedComissionErorrMessage[] =
    {
    "Stak pointer has NULL value\n",
    "Stak heap pointer has NULL value\n",
    "Wrong Stack status\n",
    "Wrong Stack capacity\n",
    "Wrong Stack top\n"    
    };

const int    IntPoison    = 0xBADDED;
const char   CharPoison   = 0;
const double DoublePoison = NAN;

//************************************ real functions
unsigned MedComissionSS (SuperStack* soldat)
    {
    unsigned flag_error = 0;

    if (soldat == NULL)
        return (flag_error |= NULL_STK_PTR_ERR);

    if (soldat->status != INITIALIZED)
        flag_error |= WRONG_STK_STATUS;
    
    if (soldat->heap == NULL)
        flag_error |= NULL_STK_HEAP;
    
    if (soldat->capacity < 0 )
        flag_error |= WRONG_STK_CAPACITY;
    
    if (soldat->top < 0)
        flag_error |= WRONG_STK_TOP;
    
    //check canary
    //if (open_dead)
    //if (clos_dead)
    //check hash

    return flag_error;
    }

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
            fprintf(dump_log, "Medcomission found error (error code %d) in stack structure: %s",
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
//************************************ end of real functions
#endif