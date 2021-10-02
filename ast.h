#ifndef crap_ast_h
#define crap_ast_h
#include "symboltable.h"
typedef enum {
    COMPOUND,
    ASSIGN,
    PRINT,
    IF,
    WHILE,
    FOR,
    IFELSE,
} StatementType; 
typedef enum {
    BINARYOP,
    LITERAL,
    IDENTIFIER,
} ExpressionType;
class Statement{
    public:
        StatementType statementtype;
        SymbolTable symboltable;
        
};

class CompoundStatement : public Statement{
    public:
        Statement* currentstatement ;
        CompoundStatement* nextstatements;
        CompoundStatement(Statement* initcurrentstatement,CompoundStatement* initnextstatements){
        }
        
};
class AssignStatement :public Statement{
    public:
        string identifier;
        Expression* expression;
        AssignStatement(string initidentifier,Expression* initexpression){}
};
class PrintStatement :public Statement{
    public:
        Expression* expression;
        PrintStatement(Expression* initexpression){
        }
};
class IfStatement :public Statement {
    public:
        Expression* condition;
        CompoundStatement* statements;
        IfStatement(Expression* initcondition,CompoundStatement* initstatements){
        }
};
class IfElseStatement :public Statement {
    public:
        Expression* condition;
        
        CompoundStatement* valid;
        CompoundStatement* invalid;
        IfElseStatement(Expression* initcondition,CompoundStatement* initvalid,CompoundStatement* initinvalid){
        }
};
class WhileStatement :public Statement{
    public:
        Expression* condition;
        CompoundStatement* statements;
        WhileStatement(Expression* initcondition,CompoundStatement* initstatements){
        }
};
class ForStatement : public Statement{
    public:
        AssignStatement* initializer;
        Expression* condition;
        AssignStatement* next;
        CompoundStatement* statements;
        ForStatement(AssignStatement* initinitializer, Expression* initcondition,AssignStatement* initnext,CompoundStatement* statements){
        }
};
class Expression{
    public:
        Type type;
        ExpressionType expressiontype;
        SymbolTable symboltable;
        void AnnotateTypes();

};
class Literal: public Expression {
    public:
        int value;
        Literal(int initvalue){

        }
        void AnnotateTypes(){}
};
class Identifier : public Expression {
    public:
        string identifier;
        Identifier(string initidentifier){

        }
        void AnnotateTypes(){
  
        }
};


class BinOp : public Expression {
    public:
        Operation* operation;
        Expression* expr1;
        Expression* expr2;
        BinOp(Operation* initoperation,Expression* initexpr1,Expression* initexpr2){

        }
        void AnnotateTypes(){}
            

};
class RelOp : public BinOp {
    public:
        RelOp(RelationalOperator* operation,Expression* expr1, Expression* expr2) : BinOp(operation,expr1,expr2)
        {}
};
class ArithmeticOp : public BinOp {
    public:
        ArithmeticOp(ArithmeticOperator* operation,Expression* expr1, Expression* expr2) : BinOp(operation,expr1,expr2)
    {}
};
class LogicalOp : public BinOp {
    public:
        LogicalOp(LogicalOperator* operation,Expression* expr1, Expression* expr2) : BinOp(operation,expr1,expr2)
    {}
        
};

#endif