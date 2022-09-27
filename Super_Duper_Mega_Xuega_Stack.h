#ifndef SUPER_DUPER_MEGA_XUEGA_STACK
#define SUPER_DUPER_MEGA_XUEGA_STACK

//******************** include 
#include <stdlib.h>
#include "my_log.h"
//******************** end of include

//******************** typedef 
//! @note if you want to change type of elements, than change this typefef
typedef int element_t; 
//******************** end of typedef

//******************** enum
enum super_stack_status
    {
    UNITILIZED,
    INITILIZED,
    INITIALIZATION_ERR
    DEAD,
    DESTRUCTOR_ERR,
    };

enum SuperStackCtorErr
    {
    NULL_STK_PTR      = -1,
    WRONG_CAPACITY    = -2,
    INITILIZED_STACK  = -3,

    SUCCESS_INITIALIZATION =  1,
    };

enum SSdump_mode // запихнуть в log.h
    {
    console   = 0,
    log_file  = 1,
    };

enum unsigned MedComissionSS_err
    {
        
    };
//******************** end of enum

//******************** struct
struct SuperStack
    {
    // opening canary

    //main
    element_t* heep;
    size_t     capacity;
    size_t     top;

    //add enum stack_status
    int stack_status = UNITILIZED;

    //hash

    //debug info
    #ifndef NDEBUG
    InitInfo dbg_inf;
    #endif

    // closing canary

    };

//#define GZHA_UNDERSTOOD true //thx Ded

/*
#ifndef NDEBUG
#define ON_SUPERDEBUG(...) __VA_ARGS__
#define SRC_LOCATION   SrcLocation   { __FILE__, __func__, __LINE__ }
//? #define DBG_INFO       DebugInitInfo { }
#else
#define ON_SUPERDEBUG(...) 
#define SRC_LOCATION 
#endif
*/
//******************** end of struct

//******************** ptotytypes

int SuperStackCtor (SuperStack* stk, int capacity);
                    //ON_SUPERDEBUG (, DebugInitInfo   dbg)  );

int SuperStackDtor (SuperStack* stk);
                    //ON_SUPERDEBUG (, SrcLocationInfo loc)  );


int       SSpush   (element_t value, int* err_flag = NULL);
                   // ON_SUPERDEBUG(, SrcLocationInfo  loc)  );

element_t SSpop    (int* err_flag = NULL);
                    //ON_SUPERDEBUG(, SrcLocationInfo  loc)  );

unsigned MedComissionSS (SuperStack* prezyvnik); //todo: check if dead

void SSdump (SuperStack* negoden, unsigned flag_err = 0, 
            SrcLocationInfo src_inf);
            //int mode = DUMP_MODE ); think about it

void* canary_calloc   (void* ptr, size_t numbers_of_elements, size_t size_of_elemet);
void* canary_recalloc (void* ptr, size_t new_numb_of_elemnts, size_t size_of_elemnt);

//void Set_dbg_inf (SuperStack* stk,       const char* stk_name, const char* init_file, 
//                  const char* init_func, const char* init_line);

int SSTop() { return ZZTop(); }; 

void FillPoison (SuperStack* stk);
//****************** end of protytypes

//****************** shells
// initialization
#define SafeStackCtor(stk_ptr, capacity) if(stk_ptr == NULL)

//kill 
#define STACK_DTOR(stk)           SuperStackDtor (stk, SRC_LOCATION);

//verificator
#define verificateSS(soldat, SrsLoc)                         \
    unsigned flag_err = MedComissionSS (soldat);                 \
    if (flag_err != 0)  SSdump (soldat, SrsLoc);


//push

//pop

//****************** end of shels

//****************** real functions
int SuperStackCtor (SuperStack* stk, int capacity
                   ON_SUPERDEBUG(, DebugInfo dbg) )
    {
    if (stk == NULL)                       return NULL_STK_PTR;
    if (capacity < 0)                      return WRONG_CAPACITY;
    if (stk -> stack_status != UNITILIZED) return INITILIZED_STACK;

    stk -> capacity = capacity;
    stk -> top      = 0;

    stk -> heep = (element_t*) canary_calloc ((void*) (stk -> heep), capacity, sizeof (element_t));
    //fil with poison
    FillPoison (stk);

    #ifndef NDEBUG
    //debug info
    stk -> dbg_inf = dbg;
    #endif

    //hash
    //not yet

    //verification 
    SrcLocationInfo SrcLoc = 
        {
        dbg.    
        }
    if ( (int flag_err = verificateSS (stk)) != 0)
        return flag_err;

    return SUCCESS_INITIALIZATION;
    }

int SuperStackDtor (SuperStack* stk);
                   // const char* FILE, const char* FUNC, const char* FUNCTION)
    {
    verificateSS(stk, LINE, FUNCTION)   
    }

// push (1.verifiacation, 2.return err code)

void* 

//****************** end of functions realisation

#endif