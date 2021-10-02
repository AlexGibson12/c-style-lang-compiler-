#include "ast.h"

CompoundStatement::CompoundStatement(Statement* initcurrentstatement,CompoundStatement* initnextstatements){
            currentstatement = initcurrentstatement;
            nextstatements = initnextstatements;
            statementtype = COMPOUND;
}

void CompleteSymbolTables(Statement* statement){
    switch(statement->statementtype){
        case COMPOUND:
            CompoundStatement* compoundstatement =(CompoundStatement*) statement;

            if((compoundstatement->currentstatement)->statementtype == ASSIGN){
                AssignStatement* currentstatement = (AssignStatement*) (compoundstatement->currentstatement);
                appendsymbol(compoundstatement->symboltable,currentstatement->identifier);  
                TrickleStartSymbolTable(compoundstatement);
                if(compoundstatement->nextstatements){
                CompleteSymbolTables(compoundstatement->nextstatements);
                }
            }else{
                CompleteSymbolTables(compoundstatement->currentstatement);
                if(compoundstatement->nextstatements){
                    CompleteSymbolTables(compoundstatement->nextstatements);
                }
            }
            break;
        case FOR:
            ForStatement* forstatement =(ForStatement*) statement;
            AssignStatement* currentstatement = (AssignStatement*) (compoundstatement->currentstatement);
            appendsymbol(forstatement->symboltable,currentstatement->identifier);  
            TrickleStartSymbolTable(forstatement);
            if(forstatement->statements){
            CompleteSymbolTables(forstatement->statements);
            }
            break;
        default:
            TrickleStartSymbolTable(statement);
            break;
    }


}

void TrickleStartSymbolTable(Statement* statement){            // Trickles symbol table down, but avoids giving assign statements references to elements it declares.
    switch(statement->statementtype){
        case COMPOUND:
            CompoundStatement* compoundstatement = (CompoundStatement*) statement;
            if((compoundstatement->currentstatement)->statementtype == ASSIGN){
                (compoundstatement->nextstatements)->symboltable = compoundstatement->symboltable;
                TrickleSymbolTableDown(compoundstatement->nextstatements);
            }else{
                (compoundstatement->currentstatement)->symboltable = compoundstatement->symboltable;
                (compoundstatement->nextstatements)->symboltable = compoundstatement->symboltable;
                TrickleSymbolTableDown(compoundstatement->currentstatement);
                TrickleSymbolTableDown(compoundstatement->nextstatements);
            }
            break;
        case ASSIGN:
            AssignStatement* assignstatement = (AssignStatement*) statement;
            (assignstatement->expression)->symboltable = assignstatement->symboltable;
            TrickleSymbolTableDown(assignstatement->expression);
            break;
        case WHILE:
            WhileStatement* whilestatement = (WhileStatement*) statement;
            (whilestatement->condition)->symboltable = whilestatement->symboltable;
            (whilestatement->statements)->symboltable = whilestatement->symboltable;
            TrickleSymbolTableDown(whilestatement->condition);
            TrickleSymbolTableDown(whilestatement->statements);
            break;
        case PRINT:
            PrintStatement* printstatement = (PrintStatement*) statement;
            (printstatement->expression)->symboltable = printstatement->symboltable;
            TrickleSymbolTableDown(printstatement->expression);
            break;
        case IF:
            IfStatement* ifstatement = (IfStatement*) statement;
            (ifstatement->condition)->symboltable = ifstatement->symboltable;
            (ifstatement->statements)->symboltable = ifstatement->symboltable;
            TrickleSymbolTableDown(ifstatement->condition);
            TrickleSymbolTableDown(ifstatement->statements);
            break;
        case IFELSE:
            IfElseStatement* ifelsestatement = (IfElseStatement*) statement;
            (ifelsestatement->condition)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->valid)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->invalid)->symboltable = ifelsestatement->symboltable;
            TrickleSymbolTableDown(ifelsestatement->condition);
            TrickleSymbolTableDown(ifelsestatement->valid);
            TrickleSymbolTableDown(ifelsestatement->invalid);
            break;
        case FOR:
            ForStatement* forstatement = (ForStatement*) statement;
            (forstatement->condition)->symboltable = forstatement->symboltable;
            (forstatement->next)->symboltable = forstatement->symboltable;
            (forstatement->statements)->symboltable = forstatement->symboltable;
            TrickleSymbolTableDown(forstatement->condition);
            TrickleSymbolTableDown(forstatement->next);
            TrickleSymbolTableDown(forstatement->statements);
            break;
    }
}
void TrickleSymbolTableDown(Statement* statement){  // Trickles symbol table down
        switch(statement->statementtype){
        case COMPOUND:
            CompoundStatement* compoundstatement = (CompoundStatement*) statement;
          
            (compoundstatement->currentstatement)->symboltable = compoundstatement->symboltable;
            (compoundstatement->nextstatements)->symboltable = compoundstatement->symboltable;
            TrickleSymbolTableDown(compoundstatement->currentstatement);
            TrickleSymbolTableDown(compoundstatement->nextstatements);
            
            break;
        case ASSIGN:
            AssignStatement* assignstatement = (AssignStatement*) statement;
            (assignstatement->expression)->symboltable = assignstatement->symboltable;
            TrickleSymbolTableDown(assignstatement->expression);
            break;
        case WHILE:
            WhileStatement* whilestatement = (WhileStatement*) statement;
            (whilestatement->condition)->symboltable = whilestatement->symboltable;
            (whilestatement->statements)->symboltable = whilestatement->symboltable;
            TrickleSymbolTableDown(whilestatement->condition);
            TrickleSymbolTableDown(whilestatement->statements);
            break;
        case PRINT:
            PrintStatement* printstatement = (PrintStatement*) statement;
            (printstatement->expression)->symboltable = printstatement->symboltable;
            TrickleSymbolTableDown(printstatement->expression);
            break;
        case IF:
            IfStatement* ifstatement = (IfStatement*) statement;
            (ifstatement->condition)->symboltable = ifstatement->symboltable;
            (ifstatement->statements)->symboltable = ifstatement->symboltable;
            TrickleSymbolTableDown(ifstatement->condition);
            TrickleSymbolTableDown(ifstatement->statements);
            break;
        case IFELSE:
            IfElseStatement* ifelsestatement = (IfElseStatement*) statement;
            (ifelsestatement->condition)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->valid)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->invalid)->symboltable = ifelsestatement->symboltable;
            TrickleSymbolTableDown(ifelsestatement->condition);
            TrickleSymbolTableDown(ifelsestatement->valid);
            TrickleSymbolTableDown(ifelsestatement->invalid);
            break;
        case FOR:
            ForStatement* forstatement = (ForStatement*) statement;
            (forstatement->initializer)->symboltable = forstatement->symboltable;
            (forstatement->condition)->symboltable = forstatement->symboltable;
            (forstatement->next)->symboltable = forstatement->symboltable;
            (forstatement->statements)->symboltable = forstatement->symboltable;
            TrickleSymbolTableDown(forstatement->initializer);
            TrickleSymbolTableDown(forstatement->condition);
            TrickleSymbolTableDown(forstatement->next);
            TrickleSymbolTableDown(forstatement->statements);
            break;
    }
}
void TrickleSymbolTableDown(Expression* expression){
      switch(expression->expressiontype){
        case BINARYOP:
            BinOp* expression = (BinOp*) expression;
            (expression->expr1)->symboltable = expression->symboltable;
            (expression->expr2)->symboltable = expression->symboltable;
            TrickleSymbolTableDown(expression->expr1);
            TrickleSymbolTableDown(expression->expr2);
            break;
    }
}
AssignStatement::AssignStatement(string initidentifier,Expression* initexpression){
            identifier = initidentifier;
            expression = initexpression;
            statementtype = ASSIGN;
        }


PrintStatement::PrintStatement(Expression* initexpression){
            expression = initexpression;
            statementtype = PRINT;
        }


IfStatement::IfStatement(Expression* initcondition,CompoundStatement* initstatements){
            condition = initcondition;
            statements = initstatements;
            statementtype = IF;
        }

IfElseStatement::IfElseStatement(Expression* initcondition,CompoundStatement* initvalid,CompoundStatement* initinvalid){
    condition = initcondition;
    valid = initvalid;
    invalid = initinvalid;    
    statementtype = IFELSE;
}
WhileStatement::WhileStatement(Expression* initcondition,CompoundStatement* initstatements){
            condition = initcondition;
            statements = initstatements;
            statementtype = WHILE;
}


ForStatement::ForStatement(AssignStatement* initinitializer, Expression* initcondition,AssignStatement* initnext,CompoundStatement* initstatements){
            initializer = initinitializer;
            condition = initcondition;
            next = initnext;
            statements = initstatements;
            statementtype = FOR;
        }



Literal::Literal(int initvalue){
    type =INT;
    expressiontype = LITERAL;
    value = initvalue;
}
  

Identifier::Identifier(string initidentifier){
            identifier = initidentifier;
            expressiontype = IDENTIFIER;
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
            expressiontype = BINARYOP;
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
        

int main() {
    CompoundStatement* x= &CompoundStatement(
        &AssignStatement(
            "x",&Literal(5)),
            &CompoundStatement(
                &WhileStatement(
                    
                    &RelOp(
                        
                    &RelationalOperator("<",""),
                    &Identifier("x"),&Literal(100)
                    ),
                    &CompoundStatement(
                    &AssignStatement("y",&Literal(1)),
                    NULL
                    )
                )
                ,NULL));
    CompleteSymbolTables(x);
}









