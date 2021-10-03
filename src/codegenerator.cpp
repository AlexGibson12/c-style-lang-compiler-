#include "../headers/codegenerator.h"

CodeGenerator::CodeGenerator(Statement* initprogram){
            program = initprogram;
        }
string CodeGenerator::emitCode(){
    string x;
    maxlabel = 0;
    maxstack = 0;
    x += "global _start\n";
    x += "extern print_number\n";
    x += "section .text:\n";
    x += "     _start:\n";
    x += "push rbp\n";
    x += "mov rbp,rsp\n";
    x += emitCode(program);
    x += "mov rax,60\n";
    x += "syscall\n";
    return x;
}   
string CodeGenerator::emitCode(Operation* operation){
    switch(operation->operation){
        case OPPLUS:{
            return "add rax,rdx\n";
        }
        case OPMINUS:{
            return "sub rax,rdx\n";
        }
        case OPLT:{
            string x;
            
            x+="cmp rax,rdx\n";
            x+=("jl .valid" + to_string(maxlabel) + "\n");
            x+=("jmp .invalid" + to_string(maxlabel+1) + "\n");
            x+=(".valid" + to_string(maxlabel) + ":\n");
            x+=("mov rax,1\n");
            x+=("jmp .either" + to_string(maxlabel+2) + "\n");
            x+=(".invalid" + to_string(maxlabel+1) + ":\n");
            x+=("mov rax,0\n");
            x+=(".either" + to_string(maxlabel+2) + ":\n");
            maxlabel+=3;
            return x;
        }
    }

}

string CodeGenerator::emitCode(Expression* expression){
    if(expression){
        switch(expression->expressiontype){
            case EXPRBINARYOP:{
                string x;
                x += emitCode(expression->expr1);
                x += emitCode(expression->expr2);
                x += "pop rdx\n";
                x += "pop rax\n";
                x += emitCode(expression->operation);
                x += "push rax\n";
                maxstack-=1;
                return x;
                break;
            }
            case EXPRIDENTIFIER:{
                string x = "push qword [rbp-" + to_string(8*(expression->symboltable.maintable[expression->identifier]->baseoffset))  + "]\n";
                maxstack+=1;
                return x;
                break;
            }
            case EXPRLITERAL:{
                string x;
                x+= "push " + to_string(expression->value) + "\n";
                maxstack+=1;
                return x;
                break;
            }
        }
    }else{
        return "";
    }
}

string  CodeGenerator::emitCode(Statement* statement){
    if(statement){
        switch(statement->statementtype){
            case STATCOMPOUND:{
                string x;
                int currentstack = maxstack;
                if(statement->nextstatements){
                    x+=emitCode(statement->currentstatement);
                    x+=emitCode(statement->nextstatements);
                    for(int i = 0;i<maxstack-currentstack-1;i++){
                        x+= "pop rax\n";
                    }
                    return x;
                }else{
                    x += emitCode(statement->currentstatement);
                    for(int i = 0;i<maxstack-currentstack-1;i++){
                        x+= "pop rax\n";
                    }
                    return x;
                }
                break;
            }
            case STATASSIGN:{
                string x;
                x += emitCode(statement->expression);
                if(statement->symboltable.maintable.find(statement->identifier) != statement->symboltable.maintable.end()){
                    x +=  "pop rax\n";
                    maxstack-=1;
                    x += ("mov [rbp-" + to_string(8*(statement->symboltable.maintable[statement->identifier]->baseoffset)) + "], rax\n");
                }
                return x;
                break;
                        }
            case STATPRINT:{
                    string x;
                    x+=emitCode(statement->expression);
                    x += "pop rax\n";
                    maxstack-=1;
                    x += "call print_number\n";
                    return x;
                    break;
            }
        }
    }else{
        return "";
    }
}

