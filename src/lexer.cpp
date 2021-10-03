#include "../headers/lexer.h"
Lexer::Lexer(string initialinput){
    input = initialinput;
    inputpointer =0 ;
}
bool Lexer::isCharacter(){
    if(inputpointer < input.size()){
        char current = input[inputpointer];
        return ('a'<=current && current<='z') || ('A'<=current && current<='Z');
    }
    return false;
}

bool Lexer::isNum(){
    return inputpointer < input.size() && '0'<=input[inputpointer] && input[inputpointer]<='9';
}
bool Lexer::isAlphaNumeric(){
    return isNum() || isCharacter();
}

Token Lexer::Identifier(){
    string ident = "";
    while(isAlphaNumeric()){
        ident += input[inputpointer];
        inputpointer++;
    }
    if(keywords.find(ident) != keywords.end()){
        return {keywords[ident],0,ident};
    }
    return {IDENTIFIER,0,ident};
}

Token Lexer::Number(){
    int l =0;
    while(isNum()){
        l = 10*l + (input[inputpointer]-'0');
        inputpointer++;
    }
    return {NUMBER,l,to_string(l)};
}
vector<Token> Lexer::tokenize(){
    vector<Token> tokens;
    inputpointer = 0;
    while(inputpointer <  input.size()){
        switch(input[inputpointer]){
            case '+':
                tokens.push_back({PLUS,0,"+"});
                inputpointer++;
                break;
            case '-':
                tokens.push_back({MINUS,0,"-"});
                inputpointer++;
                break;
            case '*':
                tokens.push_back({TIMES,0,"*"});
                inputpointer++;
                break;
            case ';':
                tokens.push_back({SEMICOLON,0,";"});
                inputpointer++;
                break;
            case '(':
                tokens.push_back({LB,0,"("});
                inputpointer++;
                break;
            case ')':
                tokens.push_back({RB,0,")"});
                inputpointer++;
                break;
            case '{':
                tokens.push_back({LBRACE,0,"{"});
                inputpointer++;
                break;
            case '}':
                tokens.push_back({RBRACE,0,"}"});
                inputpointer++;
                break;
            case '<':
                if(inputpointer+1 < input.size() and input[inputpointer+1] == '='){
                    tokens.push_back({LTE,0,"<="});
                    inputpointer+=2;
                    break;
                }
                tokens.push_back({LT,0,"<"});
                inputpointer++;
                break;
            case '!':
                if(inputpointer+1 < input.size() and input[inputpointer+1] == '='){
                    tokens.push_back({BANGEQUALS,0,"!="});
                    inputpointer+=2;
                    break;
                }
                tokens.push_back({NOT,0,"!"});
                inputpointer++;
                break;
             case '=':
                if(inputpointer+1 < input.size() and input[inputpointer+1] == '='){
                    tokens.push_back({EQUALSEQUALS,0,"=="});
                    inputpointer+=2;
                    break;
                }
                tokens.push_back({ASSIGNMENT,0,"="});
                inputpointer++;
                break;
             case '|':
                if(inputpointer+1 < input.size() and input[inputpointer+1] == '|'){
                    tokens.push_back({OR,0,"||"});
                    inputpointer+=2;
                    break;
                }
                tokens.push_back({OR,0,"||"});
                inputpointer++;
                break;
            case '&':
                if(inputpointer+1 < input.size() and input[inputpointer+1] == '&'){
                    tokens.push_back({AND,0,"&&"});
                    inputpointer+=2;
                    break;
                }
                tokens.push_back({AND,0,"&&"});
                inputpointer++;
                break;
            case '>':
                if(inputpointer+1 < input.size() and input[inputpointer+1] == '='){
                    tokens.push_back({GTE,0,">="});
                    inputpointer+=2;
                    break;
                }
                tokens.push_back({GT,0,">"});
                inputpointer++;
                break;
            default:
                if(isNum()){
                    tokens.push_back(Number());
                   
                }
                else if(isCharacter()){
                    tokens.push_back(Identifier());
                    
                }else{
                   
                    inputpointer++;
                }
                break;
                
        }

        
    }
    return tokens;
}

