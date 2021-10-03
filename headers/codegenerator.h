#ifndef crap_codegen_h
#define crap_codegen_h
#include "ast.h"
class CodeGenerator{
        public:
            Statement* program;
            int maxlabel;
            int maxstack;
            CodeGenerator(Statement* initprogram);
            string emitCode();
            string emitCode(Operation* operation);
            string emitCode(Expression* expression);
            string  emitCode(Statement* statement);
};

#endif