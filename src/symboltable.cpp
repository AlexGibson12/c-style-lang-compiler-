#include "../headers/symboltable.h"
SymbolTable::SymbolTable(){
    maintable  = map<string,symbolentry*> {};
}
SymbolTable::SymbolTable(map<string,symbolentry*> inittable){
    maintable = inittable;
}
void SymbolTable::appendsymbol(string identifier){
    if(maintable.find(identifier) == maintable.end()){
        symbolentry* newsymentry = new symbolentry {(int) maintable.size() + 1,UNCOMPLETE};
            maintable[identifier] = newsymentry ;
        }
}