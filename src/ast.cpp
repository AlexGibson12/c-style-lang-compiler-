#include "../headers/ast.h"

CompoundStatement::CompoundStatement(Statement* initcurrentstatement,CompoundStatement* initnextstatements){
            currentstatement = initcurrentstatement;
            nextstatements = initnextstatements;
            statementtype = STATCOMPOUND;
}
AssignStatement::AssignStatement(string initidentifier,Expression* initexpression){
            identifier = initidentifier;
            expression = initexpression;
            statementtype = STATASSIGN;
        }


PrintStatement::PrintStatement(Expression* initexpression){
            expression = initexpression;
            statementtype = STATPRINT;
           
        }
string emitProgram(Statement* statement){
    string x;
    x += "global _start\n";
    x += "extern print_number\n";
    x += "section .text:\n";
    x += "     _start:\n";
    x += "push rbp\n";
    x += "mov rbp,rsp\n";
    x += emitCode(statement);
    x += "mov rax,60\n";
    x += "syscall\n";
    return x;
}
string emitCode(Operation* operation){
    return operation->code;   
}
string emitCode(Expression* expression){
    if(expression){
        switch(expression->expressiontype){
            case EXPRBINARYOP:{
                  string x;
                  x += emitCode(expression->expr1);
                  x += emitCode(expression->expr2);
                  x += "pop rax\n";
                  x += "pop rdx\n";
                  x += emitCode(expression->operation);
                  x += "push rax\n";
                  return x;
                break;
            }
            case EXPRIDENTIFIER:{
                string x = "push qword [rbp-" + to_string(8*(expression->symboltable.maintable[expression->identifier]->baseoffset))  + "]\n";
                return x;
                break;
            }
            case EXPRLITERAL:{
                string x;
                x+= "push " + to_string(expression->value) + "\n";
                return x;
                break;
            }
        }
    }else{
        return "";
    }
}

string  emitCode(Statement* statement){
    if(statement){
        switch(statement->statementtype){
            case STATCOMPOUND:{
                string x;
                if(statement->nextstatements){
                    x+=emitCode(statement->currentstatement);
                    x+=emitCode(statement->nextstatements);
                    return x;
                }else{
                    return emitCode(statement->currentstatement);
                }
                break;
            }
            case STATASSIGN:{
                 string x;
                 x += emitCode(statement->expression);
                if(statement->symboltable.maintable.find(statement->identifier) != statement->symboltable.maintable.end()){
                    x +=  "pop rax\n";
                    x += ("mov [rbp-" + to_string(8*(statement->symboltable.maintable[statement->identifier]->baseoffset)) + "], rax\n");
                }
                return x;
                break;
                        }
            case STATPRINT:{
                    string x;
                    x+=emitCode(statement->expression);
                    x += "pop rax\n";
                    x += "call print_number\n";
                    return x;
                    break;
            }
        }
    }else{
        return "";
    }
}
IfStatement::IfStatement(Expression* initcondition,CompoundStatement* initstatements){
            condition = initcondition;
            statements = initstatements;
            statementtype = STATIF;
           
}


IfElseStatement::IfElseStatement(Expression* initcondition,CompoundStatement* initvalid,CompoundStatement* initinvalid){
    condition = initcondition;
    valid = initvalid;
    invalid = initinvalid;    
    statementtype = STATIFELSE;
}
WhileStatement::WhileStatement(Expression* initcondition,CompoundStatement* initstatements){
            condition = initcondition;
            statements = initstatements;
            statementtype = STATWHILE;
}


ForStatement::ForStatement(AssignStatement* initinitializer, Expression* initcondition,AssignStatement* initnext,CompoundStatement* initstatements){
            initializer = initinitializer;
            condition = initcondition;
            next = initnext;
            statements = initstatements;
            statementtype = STATFOR;
        }



Literal::Literal(int initvalue){
    type =INT;
    expressiontype = EXPRLITERAL;
    value = initvalue;
}


Identifier::Identifier(string initidentifier){
            identifier = initidentifier;
            expressiontype = EXPRIDENTIFIER;
}


BinOp::BinOp(Operation* initoperation,Expression* initexpr1,Expression* initexpr2){
            type = UNCOMPLETE;
            expressiontype = EXPRBINARYOP;
            operation = initoperation;
            expr1 = initexpr1;
            expr2 = initexpr2;
            

}

void TrickleSymbolTableDown(Expression* expression){
    if(expression){
      switch(expression->expressiontype){
        case EXPRBINARYOP:{
            (expression->expr1)->symboltable = expression->symboltable;
            (expression->expr2)->symboltable = expression->symboltable;
            TrickleSymbolTableDown(expression->expr1);
            TrickleSymbolTableDown(expression->expr2);
            break;
        }
    }
    }
}
void TrickleSymbolTableDown(Statement* statement){  // Trickles symbol table down

    if(statement){
        switch(statement->statementtype){
        case STATCOMPOUND:{
           Statement* compoundstatement =  statement;
            (compoundstatement->currentstatement)->symboltable = compoundstatement->symboltable;
            if(compoundstatement->nextstatements){
            
            (compoundstatement->nextstatements)->symboltable = compoundstatement->symboltable;
            }
         
            TrickleSymbolTableDown(compoundstatement->currentstatement);
          
            if(compoundstatement->nextstatements){
            TrickleSymbolTableDown(compoundstatement->nextstatements);
            }
            
            break;
        }
        case STATASSIGN:{
       
            Statement* assignstatement = statement;
            Expression* expr = assignstatement->expression;
           
            for(auto x: (assignstatement->symboltable).maintable){
              
            }
            (assignstatement->expression)->symboltable = assignstatement->symboltable;
        
            TrickleSymbolTableDown(assignstatement->expression);
            break;
        }
        case STATWHILE:{
        
           Statement* whilestatement =  statement;
            (whilestatement->condition)->symboltable = whilestatement->symboltable;
            (whilestatement->statements)->symboltable = whilestatement->symboltable;
            TrickleSymbolTableDown(whilestatement->condition);
            TrickleSymbolTableDown(whilestatement->statements);
            break;
        }
        case STATPRINT:{
            Statement* printstatement =  statement;
            (printstatement->expression)->symboltable = printstatement->symboltable;
            TrickleSymbolTableDown(printstatement->expression);
            break;
        }
        case STATIF:{
            Statement* ifstatement = statement;
            (ifstatement->condition)->symboltable = ifstatement->symboltable;
            (ifstatement->statements)->symboltable = ifstatement->symboltable;
            TrickleSymbolTableDown(ifstatement->condition);
            TrickleSymbolTableDown(ifstatement->statements);
            break;
        }
        case STATIFELSE:{
            Statement* ifelsestatement = statement;
            (ifelsestatement->condition)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->valid)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->invalid)->symboltable = ifelsestatement->symboltable;
            TrickleSymbolTableDown(ifelsestatement->condition);
            TrickleSymbolTableDown(ifelsestatement->valid);
            TrickleSymbolTableDown(ifelsestatement->invalid);
            break;
        }
        case STATFOR:{
            Statement* forstatement = statement;
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
    }
}

void TrickleStartSymbolTable(Statement* statement){  
  
    if(statement){
    switch(statement->statementtype){
        case STATCOMPOUND:{
            Statement* compoundstatement =statement;
           
             if((compoundstatement->currentstatement)->statementtype == STATASSIGN){
           
                 if(compoundstatement->nextstatements){
               
                (compoundstatement->nextstatements)->symboltable = (compoundstatement->symboltable);
                TrickleSymbolTableDown(compoundstatement->nextstatements);
                 }
            }else{
           
                (compoundstatement->currentstatement)->symboltable = compoundstatement->symboltable;
                if(compoundstatement->nextstatements){
                (compoundstatement->nextstatements)->symboltable = compoundstatement->symboltable;
                }
                TrickleSymbolTableDown(compoundstatement->currentstatement);
                if(compoundstatement->nextstatements){
                TrickleSymbolTableDown(compoundstatement->nextstatements);
                }
            }
            break;
        }
        case STATASSIGN:{
            Statement* assignstatement = statement;
            (assignstatement->expression)->symboltable = assignstatement->symboltable;
            TrickleSymbolTableDown(assignstatement->expression);
            break;
        }
        case STATWHILE:{
            Statement* whilestatement =statement;
            (whilestatement->condition)->symboltable = whilestatement->symboltable;
            if(whilestatement->statements){
            (whilestatement->statements)->symboltable = whilestatement->symboltable;
            }
            TrickleSymbolTableDown(whilestatement->condition);
            if(whilestatement->statements){
            CompleteSymbolTables(whilestatement->statements);
            }
            break;
        }
        case STATPRINT:{
            Statement* printstatement =  statement;
            (printstatement->expression)->symboltable = printstatement->symboltable;
            TrickleSymbolTableDown(printstatement->expression);
            break;
        }
        case STATIF:{
            Statement* ifstatement = statement;
            (ifstatement->condition)->symboltable = ifstatement->symboltable;
            (ifstatement->statements)->symboltable = ifstatement->symboltable;
            TrickleSymbolTableDown(ifstatement->condition);
            CompleteSymbolTables(ifstatement->statements);
            break;
        }
        case STATIFELSE:{
            Statement* ifelsestatement =statement;
            (ifelsestatement->condition)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->valid)->symboltable = ifelsestatement->symboltable;
            (ifelsestatement->invalid)->symboltable = ifelsestatement->symboltable;
            TrickleSymbolTableDown(ifelsestatement->condition);
            CompleteSymbolTables(ifelsestatement->valid);
            CompleteSymbolTables(ifelsestatement->invalid);
            break;
        }
        case STATFOR:{
            Statement* forstatement =  statement;
            (forstatement->condition)->symboltable = forstatement->symboltable;
            (forstatement->next)->symboltable = forstatement->symboltable;
            (forstatement->statements)->symboltable = forstatement->symboltable;
            TrickleSymbolTableDown(forstatement->condition);
            TrickleSymbolTableDown(forstatement->next);
            CompleteSymbolTables(forstatement->statements);
            break;
        }
    }
    }
}

void CompleteSymbolTables(Statement* statement){
    if(statement){
    Statement* compoundstatement = statement;

    switch(statement->statementtype){
        
        case STATCOMPOUND:{
            if((compoundstatement->currentstatement)->statementtype == STATASSIGN){
                
                Statement* currentstatement =  (compoundstatement->currentstatement);
                compoundstatement->symboltable.appendsymbol(currentstatement->identifier);
                
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
        }
        case STATFOR:{
            Statement* forstatement = statement;
            Statement* currentstatement =  (compoundstatement->currentstatement);
            forstatement->symboltable.appendsymbol(currentstatement->identifier);  
            TrickleStartSymbolTable(forstatement);
            if(forstatement->statements){
            CompleteSymbolTables(forstatement->statements);
            }
            break;
        }
        default:{
            TrickleStartSymbolTable(statement);
            break;
        }
    }
    }


}



