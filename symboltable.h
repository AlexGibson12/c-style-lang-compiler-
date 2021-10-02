#ifndef crap_symboltable_h
#define crap_symboltable_h
#include "types.h"
typedef struct {
    int baseoffset;
    Type type;
} symbolentry;
typedef map<string,symbolentry> SymbolTable;
void appendsymbol(SymbolTable& symboltable, string identifier ){
    if(symboltable.find(identifier) == symboltable.end()){
        symboltable[identifier] = {(int) symboltable.size() + 1,UNCOMPLETE};
    }
}
#endif