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



Literal::Literal(int initvalue){
    type =INT;
    value = initvalue;
}
  

Identifier::Identifier(string initidentifier){
            identifier = initidentifier;
}
void Identifier::AnnotateTypes(){
    if(symboltable.find(identifier) != symboltable.end()){
        type = symboltable[identifier].type;
    }else{
        type = UNKNOWN;
    }
}




BinOp::BinOp(Operation* initoperation,Expression* initexpr1,Expression* initexpr2){
            type = UNCOMPLETE;
            operation = initoperation;
            expr1 = initexpr1;
            expr2 = initexpr2;
}
void BinOp::AnnotateTypes(){
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
            