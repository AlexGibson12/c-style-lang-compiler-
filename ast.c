#include "ast.h"

CompoundStatement::CompoundStatement(Statement* initcurrentstatement,CompoundStatement* initnextstatements){
            currentstatement = initcurrentstatement;
            nextstatements = initnextstatements;
}
    

AssignStatement::AssignStatement(string initidentifier,Expression* initexpression){
            identifier = initidentifier;
            expression = initexpression;
        }


PrintStatement::PrintStatement(Expression* initexpression){
            expression = initexpression;
        }


IfStatement::IfStatement(Expression* initcondition,CompoundStatement* initstatements){
            condition = initcondition;
            statements = initstatements;
        }


WhileStatement::WhileStatement(Expression* initcondition,CompoundStatement* initstatements){
            condition = initcondition;
            statements = initstatements;
}


ForStatement::ForStatement(AssignStatement* initinitializer, Expression* initcondition,AssignStatement* initnext){
            initializer = initinitializer;
            condition = initcondition;
            next = initnext;
        }

class Expression{
    public:
        Type type = UNCOMPLETE;
        SymbolTable symboltable;
        void AnnotateTypes();

};

Literal::Literal(int initvalue){
            type =INT;
            value = initvalue;
        }
  

Identifier::Identifier(string initidentifier){
            identifier = initidentifier;
        }
Identifier::AnnotateTypes(){
            if(SymbolTable.find(identifier) != SymbolTable.end()){
                type = SymbolTable[identifier];
            }else{
                type = UNKNOWN;
            }
        }



class BinOp : public Expression {
    public:
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
