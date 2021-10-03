#ifndef crap_ast_h
#define crap_ast_h
#include "symboltable.h"
typedef enum {
    STATCOMPOUND,
    STATASSIGN,
    STATPRINT,
    STATIF,
    STATWHILE,
    STATFOR,
    STATIFELSE,
} StatementType; 
typedef enum {
    EXPRBINARYOP,
    EXPRLITERAL,
    EXPRIDENTIFIER,
} ExpressionType;
class Expression{
    public:
        Type type;
        ExpressionType expressiontype;
        SymbolTable symboltable;
        string identifier;
        int value;
        Operation* operation;
        Expression* expr1;
        Expression* expr2;
        void AnnotateTypes();
        string emitCode(){return "";};
};
class CompoundStatement;
class AssignStatement;

class Statement{
    public:
        StatementType statementtype;
        SymbolTable symboltable;
        string identifier;
        CompoundStatement* nextstatements;
        Statement* currentstatement;
        Expression* expression;
        Expression* condition; 
        CompoundStatement* statements; 
        CompoundStatement* valid;
        CompoundStatement* invalid;
        AssignStatement* initializer;
        AssignStatement* next;
        string emitCode(){ return ""; };
};

class CompoundStatement : public Statement{
    public:

        CompoundStatement(Statement* initcurrentstatement,CompoundStatement* initnextstatements);
      
        
};
class AssignStatement :public Statement{
    public:
        AssignStatement(string initidentifier,Expression* initexpression);
   
};
class PrintStatement :public Statement{
    public:
        PrintStatement(Expression* initexpression);
       
};
class IfStatement :public Statement {
    public:
 
        IfStatement(Expression* initcondition,CompoundStatement* initstatements);
      
};
class IfElseStatement :public Statement {
    public:
    
        IfElseStatement(Expression* initcondition,CompoundStatement* initvalid,CompoundStatement* initinvalid);
       
};
class WhileStatement :public Statement{
    public:

        WhileStatement(Expression* initcondition,CompoundStatement* initstatements);
   
};
class ForStatement : public Statement{
    public:
     
        ForStatement(AssignStatement* initinitializer, Expression* initcondition,AssignStatement* initnext,CompoundStatement* statements);
       
};

class Literal: public Expression {
    public:
        Literal(int initvalue);
        void AnnotateTypes();
       
};
class Identifier : public Expression {
    public:
        Identifier(string initidentifier);
        void AnnotateTypes();
        
};


class BinOp : public Expression {
    public:

        BinOp(Operation* initoperation,Expression* initexpr1,Expression* initexpr2);
        void AnnotateTypes();
        
            

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