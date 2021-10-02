#ifndef crap_symboltable_h
#define crap_symboltable_h
#include "types.h"
typedef struct {
    int baseoffset;
    Type type;
} symbolentry;
typedef map<string,symbolentry> SymbolTable;
#endif