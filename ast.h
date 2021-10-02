#ifndef crap_ast_h
#define crap_ast_h
#include "common.h"
#include "types.h"
class Statement{
    public:
        map<string,int> identifiernames;
        
};
class CompoundStatement : public Statement{
    public:
        Statement* currentstatement ;
        CompoundStatement* nextstatements;
        CompoundStatement(Statement* initcurrentstatement,CompoundStatement* initnextstatements){
            currentstatement = initcurrentstatement;
            nextstatements = initnextstatements;
        }
        
};
class AssignStatement :public Statement{
    public:
        string identifier;
        Expression* expression;
        AssignStatement(string initidentifier,Expression* initexpression){
            identifier = initidentifier;
            expression = initexpression;
        }
};
class PrintStatement :public Statement{
    public:
        Expression* expression;
        PrintStatement(Expression* initexpression){
            expression = initexpression;
        }
};
class IfStatement :public Statement {
    public:
        Expression* condition;
        CompoundStatement* statements;
        IfStatement(Expression* initcondition,CompoundStatement* initstatements){
            condition = initcondition;
            statements = initstatements;
        }
};
class WhileStatement :public Statement{
    public:
        Expression* condition;
        CompoundStatement* statements;
        WhileStatement(Expression* initcondition,CompoundStatement* initstatements){
            condition = initcondition;
            statements = initstatements;
        }
};
class ForStatement : public Statement{
    public:
        AssignStatement* initializer;
        Expression* condition;
        AssignStatement* next;
        ForStatement(AssignStatement* initinitializer, Expression* initcondition,AssignStatement* initnext){
            initializer = initinitializer;
            condition = initcondition;
            next = initnext;
        }
};
class Expression{
    public:
        Type type = UNCOMPLETE;
        map<string,int> identifiernames;
        void AnnotateTypes();

};
class Literal: public Expression {

}
class Identifier : public Expression {
    public:
        
};


class BinOp : public Expression {
    public:
        Operation* operation;
        Expression* expr1;
        Expression* expr2;
        BinOp(Operation* initoperation,Expression* initexpr1,Expression* initexpr2){
            operation = initoperation;
            expr1 = initexpr1;
            expr2 = initexpr2;
        }
        void AnnotateTypes(){
            if(expr1->type == UNCOMPLETE){
                expr1->AnnotateTypes();
            }
            if(expr2->type == UNCOMPLETE){
                expr2->AnnotateTypes();
            }
            if((operation->typetable).find({expr1->type,expr2->type}) != (operation->typetable).end()){
                type = (operation->typetable)[{expr1->type,expr2->type}];
            }else{
                type = UNKNOWN;
            }

        }
            

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
void InitializeIdentifiers(CompoundStatement* compound);
void AnnotateTypes(CompoundStatement* compound);

#endif