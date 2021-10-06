#include "../headers/codegenerator.h"

CodeGenerator::CodeGenerator(Statement* initprogram){
            program = initprogram;
        }
string CodeGenerator::emitCode(){
    string x;
    maxlabel = 0;
    maxstack = 0;
    x += "section .text\n";
    x += "extern print_number\n";
    x += "global _start\n";
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
        case OPMODULO:{
            string x;
            x+="push rcx\n";
            maxstack +=1;
            x+="mov rcx,rdx\n";
            x+="xor rdx,rdx\n";
            x+= "div rcx\n";
            x+="pop rcx\n";
            maxstack-=1;
            x+= "mov rax,rdx\n";
            return x;
        }
          case OPTIMES:{
            return "mul rdx\n";
        }
        case OPMINUS:{
            return "sub rax,rdx\n";
        }
        case OPEQUAL:{
            string x;
            
            x+="cmp rax,rdx\n";
            x+=("je .valid" + to_string(maxlabel) + "\n");
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
        case OPLTE:{
            string x;
            
            x+="cmp rax,rdx\n";
            x+=("jng .valid" + to_string(maxlabel) + "\n");
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
        case OPGT:{
            string x;
            
            x+="cmp rax,rdx\n";
            x+=("jg .valid" + to_string(maxlabel) + "\n");
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
        case OPGTE:{
            string x;
            
            x+="cmp rax,rdx\n";
            x+=("jnl .valid" + to_string(maxlabel) + "\n");
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
                maxstack-=2;
                x += emitCode(expression->operation);
                x += "push rax\n";
                maxstack+=1;
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
                    for(int i = 0;i<maxstack-currentstack;i++){
                        x+= "pop rax\n";
                    }
                    maxstack = currentstack;
                    return x;
                }else{
                    x += emitCode(statement->currentstatement);
                    for(int i = 0;i<maxstack-currentstack;i++){
                        x+= "pop rax\n";
                    }
                    maxstack = currentstack;
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
            case STATWHILE:{
                string x;
                maxlabel+=1;
                int whilelabel = maxlabel;
                
                x+=(".while" + to_string(whilelabel) + ":\n");
               
                x+=emitCode(statement->condition);
                int pastlabel = maxlabel+1;
                maxlabel +=1;
                x+="pop rax\n";
                maxstack-=1;
                x+="cmp rax,0\n";
                x+=("je .pastwhile" + to_string(pastlabel) + "\n");
                x+=emitCode(statement->statements);
                x+=("jmp .while" + to_string(whilelabel)+"\n");
                x+= (".pastwhile" + to_string(pastlabel) + ":\n");

                maxlabel+=2;
                return x;
            }
            case STATIFELSE:{
                string x;
             
                maxlabel+=1;
                int iflabel = maxlabel;
                x+=emitCode(statement->condition);
                x+="pop rax\n";
                maxstack-=1;
                x+="cmp rax,0\n";
                x+=("jne .ifstat"+to_string(iflabel)+"\n");
                maxlabel+=1;
                int elselabel = maxlabel;
                maxlabel+=1;
                int endlabel = maxlabel;
                x+=("jmp .elsestat" + to_string(elselabel) + "\n");
                x+=(".ifstat"+to_string(iflabel) + ":\n");
                x+=emitCode(statement->valid);
                x+=("jmp .done" + to_string(endlabel) + "\n");
                x+=(".elsestat" + to_string(elselabel) + ":\n");
                x+=emitCode(statement->invalid);
                x+=("jmp .done" + to_string(endlabel) + "\n");
                x+=(".done" + to_string(endlabel)+":\n");
                maxlabel+=1;
                return x;
                break;
            }
            case STATIF:{
                string x;
                maxlabel+=1;
                int iflabel = maxlabel;
                x+=emitCode(statement->condition);
                x+="pop rax\n";
                maxstack-=1;
                x+="cmp rax,0\n";
                x+=("jne .ifstat"+to_string(iflabel)+"\n");
                int donelabel = maxlabel;
                x+=("jmp .done" + to_string(donelabel) + "\n");
                x+=(".ifstat" + to_string(iflabel) + ":\n");
                x+=emitCode(statement->statements);
                x+=(".done" + to_string(donelabel)+":\n");
                maxlabel+=1;
                return x;
            }
        }
    }else{
        return "";
    }
}

