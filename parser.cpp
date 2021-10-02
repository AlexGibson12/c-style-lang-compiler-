#include "parser.h"

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
    Expression*  plusfactor = PlusFactor();
    Expression * right = GreaterRight();
    if(right){
        RelationalOperator* reloperator = new RelationalOperator("<","");
        Expression* expressionstuff = new RelOp {reloperator,plusfactor,right};
    }else{
        return plusfactor;
    }
   
}
Expression* Parser::GreaterRight(){
    if(currenttoken.type == LT){
         Match('<');
         Expression* plusfactore = PlusFactor();
         Expression* right = GreaterRight();
         if(right){
             RelationalOperator* reloperator = new RelationalOperator("<","");
             Expression* expressionstuff = new RelOp {reloperator,plusfactore,right};
         }else{
             return plusfactore;
         }
    }
    return NULL;
   

}
Expression* Parser::PlusFactor(){
    Expression* factore = Factor();
    ArithmeticOperator* addoperator = new ArithmeticOperator{"+",""};
    while(currenttoken.type == PLUS){
        Match('+');
        Expression* nextfactor = Factor();
        factore = new ArithmeticOp{addoperator,factore,nextfactor};
    }
    return factore;
}

Statement* Parser::consumeprint(){
    Match('p');
    Match('(');
    Expression* resultexpr = expression();

    Match(')');
    Statement* printstate = new PrintStatement {resultexpr};
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
    Statement* assignment = new AssignStatement {identname,resultexpr};
    return assignment;
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
        case IDENTIFIER:
            resultstate = consumeassign();
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
int main(){
    ifstream fin;
    fin.open("input.txt",ios::in);
    string input;
    string x;
    while(fin>>x){
        input+=x;
        input+=" ";
    }
    Lexer lex = Lexer(input);
    vector<Token> tokens = lex.tokenize();
    for(auto x: tokens){
        cout << x.name << " " << x.type << " " << x.value << endl;
    }
    Parser parse = Parser(tokens);
    CompoundStatement* statementsa = parse.Parse();

    cout << "WIN" << endl;
    cout << (statementsa->nextstatements)->statementtype << endl;
    cout << "WONG" << endl;
    CompleteSymbolTables(statementsa);
    for(auto& x : (((statementsa->nextstatements))->symboltable).maintable){
        cout << x.first;
    }

}



