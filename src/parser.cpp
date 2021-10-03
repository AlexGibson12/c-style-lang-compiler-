#include "../headers/parser.h"
#include "../headers/scope.h"
Parser::Parser(vector<Token> inittokens){
    tokens = inittokens;
}
void Parser::Match(char ch){
    inputpointer++;

    if(inputpointer < tokens.size()){
        currenttoken = tokens[inputpointer];
 
    }else{
        currenttoken =  {END,0,"EOF"};
    }
}
Expression* Parser::Factor(){
    switch(currenttoken.type){
        case LB:{
            Match('(');
            Expression* exprfac = expression();
            Match(')');
            return exprfac;
            break;
        }
        case IDENTIFIER:{
            Expression* exprident = new Identifier { currenttoken.name };
            Match('h');
            return exprident;
            break;
        }
        case NUMBER:{
            Expression* exprnum = new Literal {currenttoken.value};
            Match('w');
            return exprnum;
            break;
        }
        default:{
            return NULL;
            break;
        }

    }
}
Expression* Parser::expression(){
    return GreaterRight();
   
}
Expression* Parser::GreaterRight(){
    Expression* plusfactore = PlusFactor();
    RelationalOperator* reloperator = new RelationalOperator(OPLT);
   
    while(currenttoken.type == LT){
        Match('<');
    
        Expression* nextfactor = PlusFactor();
 
        plusfactore = new RelOp{reloperator,plusfactore,nextfactor};
    }
    return plusfactore;
}
Expression* Parser::PlusFactor(){
    Expression* factore = Factor();
    ArithmeticOperator* mainoperator;
    ArithmeticOperator* addoperator = new ArithmeticOperator{OPPLUS};
    ArithmeticOperator* minusoperator = new ArithmeticOperator(OPMINUS);
    while(currenttoken.type == PLUS or currenttoken.type == MINUS){
            if(currenttoken.type == PLUS){
            mainoperator = addoperator;
        }else{
            mainoperator = minusoperator;
        }
        Match('+');
     
        Expression* nextfactor = Factor();
       
        factore = new ArithmeticOp{mainoperator,factore,nextfactor};
    }
    return factore;
}

Statement* Parser::consumeprint(){
    Match('p');
    Match('(');
    Expression* resultexpr = expression();

    Match(')');
    Statement* printstate = new PrintStatement {resultexpr};
    Match(';');
    return printstate;
}
Statement* Parser::consumewhile(){
    Match('w');
    Match('(');
    Expression* cond = expression();

    Match(')');

    CompoundStatement* compoundstat= compound();
    Statement* whilestat = new WhileStatement {cond,compoundstat};
    return whilestat;
}
Statement* Parser::consumeassign(){

    string identname = currenttoken.name;
    Match('w');
    Match('=');
    Expression* resultexpr = expression();
    Match(';');
    Statement* assignment = new AssignStatement {identname,resultexpr};
    return assignment;
}
Statement* Parser::consumefor(){

}
Statement* Parser::consumeifelse(){
    Match('i');
    Match('(');
    Expression* cond = expression();
    Match(')');
    CompoundStatement* compoundstat = compound();
    if(currenttoken.type == ELSE){
        Match('e');
        CompoundStatement* compoundstat2 = compound();
        Statement* ifelsestat = new IfElseStatement {cond,compoundstat,compoundstat2};
        return ifelsestat;
    }else{
        Statement* ifstat = new IfStatement {cond,compoundstat};
        cout << "GOT HERE";
        return ifstat;
    }
}
CompoundStatement* Parser::statements(){
    //Identifying start of statement - either identifier or print or while
    Statement* resultstate;

    switch(currenttoken.type){
        case PRINT:
            resultstate = consumeprint();
            break;
        case WHILE:
            resultstate = consumewhile();
            break;
        case IF:
            resultstate = consumeifelse();
            break;
        case IDENTIFIER:
            resultstate = consumeassign();
            break;
        case LBRACE:
            resultstate = compound();
            break;
        default: 
            return NULL;
            break;
    }
    CompoundStatement* compstate =  (CompoundStatement*) new CompoundStatement {resultstate,statements()};
    return compstate;
}
CompoundStatement* Parser::Parse(){
    inputpointer = 0;
    currenttoken = tokens[inputpointer];

    return statements();
}
CompoundStatement* Parser::compound(){
    Match('{');

    CompoundStatement* resultstate= statements();
    Match('}');
 
    return resultstate;
}


