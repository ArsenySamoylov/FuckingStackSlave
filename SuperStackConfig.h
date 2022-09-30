#ifndef STACK_CONFIG
#define STACK_CONGIG

//************************************ include 

//************************************ end of include files

//************************************ typedef 
//! @note if you want to change type of elements, than change this typefef
typedef int element_t; 
//******************** end of typedef

//************************************ enum
enum super_stack_status
    {
    UNINITIALIZED, // spelling
    INITIALIZED,
    INITIALIZATION_ERR,
    DEAD,
    DESTRUCTOR_ERR, //WALKING_DEAD
    };
//************************************ end of enum
#endif