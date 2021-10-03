#ifndef crap_symboltable_h
#define crap_symboltable_h
#include "types.h"

class SymbolTable {
    public:
        typedef struct { int baseoffset; Type type;} symbolentry;
        map<string,symbolentry*> maintable;
        SymbolTable();
        SymbolTable(map<string,symbolentry*> inittable);
        void appendsymbol(string identifier);
};
#endif