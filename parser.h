#ifndef crap_ast_h
#define crap_ast_h
#include "common.h"
class Statement{
    public:
        map<string,int> identifiernames;
        
};
class CompoundStatement{
    public:
        Statement* Current ;
        CompoundStatement* nextstatements;
        
};
class AssignStatement {
    public:

}   ;
class PrintStatement {

};
class IfStatement {
    public:
        map<string,int> iden;
};
class Expression{
    public:
        string type;
        map<string,int> identifiernames;


};
class RelOp : public Expression {
    public:
        string type = "bool";
        string operatortype;
        Expression* expr1;
        Expression* expr2;
        

};
class BinOp : public Expression {
    public:
        string type = "int";
        string operatortype;
        Expression* expr1;
        Expression* expr2;

};
#endif


