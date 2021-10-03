#ifndef crap_types_h
#define crap_types_h
#include "common.h"
typedef enum {
    INT,
    BOOL,
    UNKNOWN,
    UNCOMPLETE,
} Type;
typedef enum {
    OPPLUS,
    OPTIMES,
    OPMOD,
    OPMINUS,
    OPAND,
    OPOR,
    OPLT,
    OPLTE,
    OPGT,
    OPGTE,
    OPNOT,
    OPEQUAL,
    OPMODULO,
} OperationType;
class Operation {
    public:
        map<pair<Type,Type>,Type> typetable;
        OperationType operation;

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
        RelationalOperator(OperationType initoperation){
            typetable = {{{INT,INT},BOOL},{{INT,BOOL},UNKNOWN},{{BOOL,INT},UNKNOWN},{{BOOL,BOOL},UNKNOWN}};
            operation = initoperation;

        }
};
class ArithmeticOperator : public Operation {
    public:
         ArithmeticOperator(OperationType initoperation){
            typetable = {{{INT,INT},INT},{{INT,BOOL},UNKNOWN},{{BOOL,INT},UNKNOWN},{{BOOL,BOOL},UNKNOWN}};
            operation = initoperation;
        }
        
};
class LogicalOperator : public Operation {
    public:
         LogicalOperator(OperationType initoperation){
            typetable = {{{INT,INT},UNKNOWN},{{INT,BOOL},UNKNOWN},{{BOOL,INT},UNKNOWN},{{BOOL,BOOL},BOOL}};
            operation = initoperation;
        }
};





#endif