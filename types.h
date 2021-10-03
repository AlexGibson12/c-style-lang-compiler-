#ifndef crap_types_h
#define crap_types_h
#include "common.h"
typedef enum {
    INT,
    BOOL,
    UNKNOWN,
    UNCOMPLETE,
} Type;
class Operation {
    public:
        map<pair<Type,Type>,Type> typetable;
        string operation;
        string code;

        Type newType(Type type1, Type type2){
            pair<Type,Type> typepair = {type1,type2};
            if(typetable.find(typepair) != typetable.end()){
                
            }else{
                return UNKNOWN; 
            }
        }
       
};
class RelationalOperator : public Operation {
    public:
        RelationalOperator(string initoperation,string initcode){
            typetable = {{{INT,INT},BOOL},{{INT,BOOL},UNKNOWN},{{BOOL,INT},UNKNOWN},{{BOOL,BOOL},UNKNOWN}};
            operation = initoperation;
            code = initcode;
        }
};
class ArithmeticOperator : public Operation {
    public:
         ArithmeticOperator(string initoperation,string initcode){
            typetable = {{{INT,INT},INT},{{INT,BOOL},UNKNOWN},{{BOOL,INT},UNKNOWN},{{BOOL,BOOL},UNKNOWN}};
            operation = initoperation;
            code = initcode;
        }
        
};
class LogicalOperator : public Operation {
    public:
         LogicalOperator(string initoperation,string initcode){
            typetable = {{{INT,INT},UNKNOWN},{{INT,BOOL},UNKNOWN},{{BOOL,INT},UNKNOWN},{{BOOL,BOOL},BOOL}};
            operation = initoperation;
            code = initcode;
        }
};





#endif