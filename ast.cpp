#include "ast.h"

CompoundStatement::CompoundStatement(Statement* initcurrentstatement,CompoundStatement* initnextstatements){
            currentstatement = initcurrentstatement;
            nextstatements = initnextstatements;
            statementtype = COMPOUND;
}
CompoundStatement* compoundstatement;
AssignStatement* assignstatement;
WhileStatement* whilestatement;
PrintStatement* printstatement;
IfStatement* ifstatement;
IfElseStatement* ifelsestatement;
ForStatement* forstatement;
AssignStatement* currentstatement;
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
void TrickleSymbolTableDown(Statement* statement){  // Trickles symbol table down
        switch(statement->statementtype){
        case COMPOUND:
            compoundstatement = (CompoundStatement*) statement;
          
            (compoundstatement->currentstatement)->symboltable = compoundstatement->symboltable;
            (compoundstatement->nextstatements)->symboltable = compoundstatement->symboltable;
            TrickleSymbolTableDown(compoundstatement->currentstatement);
            TrickleSymbolTableDown(compoundstatement->nextstatements);
            
            break;
        case ASSIGN:
            assignstatement = (AssignStatement*) statement;
            (assignstatement->expression)->symboltable = assignstatement->symboltable;
            TrickleSymbolTableDown(assignstatement->expression);
            break;
        case WHILE:
            whilestatement = (WhileStatement*) statement;
            (whilestatement->condition)->symboltable = whilestatement->symboltable;
            (whilestatement->statements)->symboltable = whilestatement->symboltable;
            TrickleSymbolTableDown(whilestatement->condition);
            TrickleSymbolTableDown(whilestatement->statements);
            break;
        case PRINT:
            printstatement = (PrintStatement*) statement;
            (printstatement->expression)->symboltable = printstatement->symboltable;
            TrickleSymbolTableDown(printstatement->expression);
            break;
        case IF:
            ifstatement = (IfStatement*) statement;
            (ifstatement->condition)->symboltable = ifstatement->symboltable;
            (ifstatement->statements)->symboltable = ifstatement->symboltable;
            TrickleSymbolTableDown(ifstatement->condition);
            TrickleSymbolTableDown(ifstatement->statements);
            break;
        case IFELSE:
            ifelsestatement = (IfElseStatement*) statement;
            (ifelsestatement->condition)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->valid)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->invalid)->symboltable = ifelsestatement->symboltable;
            TrickleSymbolTableDown(ifelsestatement->condition);
            TrickleSymbolTableDown(ifelsestatement->valid);
            TrickleSymbolTableDown(ifelsestatement->invalid);
            break;
        case FOR:
            forstatement = (ForStatement*) statement;
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

void TrickleStartSymbolTable(Statement* statement){            // Trickles symbol table down, but avoids giving assign statements references to elements it declares.
    switch(statement->statementtype){
        case COMPOUND:
            compoundstatement = (CompoundStatement*) statement;
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
            assignstatement = (AssignStatement*) statement;
            (assignstatement->expression)->symboltable = assignstatement->symboltable;
            TrickleSymbolTableDown(assignstatement->expression);
            break;
        case WHILE:
            whilestatement = (WhileStatement*) statement;
            (whilestatement->condition)->symboltable = whilestatement->symboltable;
            (whilestatement->statements)->symboltable = whilestatement->symboltable;
            TrickleSymbolTableDown(whilestatement->condition);
            TrickleSymbolTableDown(whilestatement->statements);
            break;
        case PRINT:
            printstatement = (PrintStatement*) statement;
            (printstatement->expression)->symboltable = printstatement->symboltable;
            TrickleSymbolTableDown(printstatement->expression);
            break;
        case IF:
            ifstatement = (IfStatement*) statement;
            (ifstatement->condition)->symboltable = ifstatement->symboltable;
            (ifstatement->statements)->symboltable = ifstatement->symboltable;
            TrickleSymbolTableDown(ifstatement->condition);
            TrickleSymbolTableDown(ifstatement->statements);
            break;
        case IFELSE:
            ifelsestatement = (IfElseStatement*) statement;
            (ifelsestatement->condition)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->valid)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->invalid)->symboltable = ifelsestatement->symboltable;
            TrickleSymbolTableDown(ifelsestatement->condition);
            TrickleSymbolTableDown(ifelsestatement->valid);
            TrickleSymbolTableDown(ifelsestatement->invalid);
            break;
        case FOR:
            forstatement = (ForStatement*) statement;
            (forstatement->condition)->symboltable = forstatement->symboltable;
            (forstatement->next)->symboltable = forstatement->symboltable;
            (forstatement->statements)->symboltable = forstatement->symboltable;
            TrickleSymbolTableDown(forstatement->condition);
            TrickleSymbolTableDown(forstatement->next);
            TrickleSymbolTableDown(forstatement->statements);
            break;
    }
}

void CompleteSymbolTables(Statement* statement){
    switch(statement->statementtype){
        case COMPOUND:
            compoundstatement =(CompoundStatement*) statement;

            if((compoundstatement->currentstatement)->statementtype == ASSIGN){
                currentstatement = (AssignStatement*) (compoundstatement->currentstatement);
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
            forstatement =(ForStatement*) statement;
            currentstatement = (AssignStatement*) (compoundstatement->currentstatement);
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

