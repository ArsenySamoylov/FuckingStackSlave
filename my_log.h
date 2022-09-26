#ifndef MY_LOG
#define MY_LOG

struct DebugInitInfo
    {
    const char* var_name;
    const char* init_file;
    const char* init_function;
    const int   init_line;
    };

struct SrcLocationInfo
    {
    const char* src_file;
    const char* src_function;
    const int   src_line;
    };

//#var как избавиться от *?
#define set_init_inf(stk_ptr) (stk_ptr -> DebugInitInfo {#var, __FILE__, })