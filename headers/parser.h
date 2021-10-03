#ifndef crap_parser_h
#define crap_parser_h
#include "ast.h"
#include "lexer.h"
class Parser{
    public:
        vector<Token> tokens;
        Token currenttoken;
        long unsigned int inputpointer;
        Parser(vector<Token> tokens);
        CompoundStatement* Parse();


        void Match(char ch);
        Statement* consumewhile();
        Statement* consumeprint();
        Statement* consumeassign();
        Statement* consumeifelse();
        Statement* consumefor();
        Expression* expression();
        Expression* GreaterRight();
        Expression* PlusFactor();
        Expression* PlusRight();
        Expression* Factor();
        CompoundStatement* statements();
        CompoundStatement* compound();
      
};
#endif


