#include "../headers/parser.h"
#include "../headers/scope.h"
#include "../headers/codegenerator.h"
int main(int argc, char** argv){
    ifstream fin;
    if(argc == 2){
        fin.open(argv[1],ios::in);
    }else{
        return -1;
    }
    string input;
    string x;
    while(fin >> x){
        input += x;
        x += " ";
    }
    Lexer lex = Lexer(input);
    vector<Token> tokens = lex.tokenize();
   
    Parser parse = Parser(tokens);

    CompoundStatement* statementsa = parse.Parse();

    CompleteSymbolTables(statementsa);
    CodeGenerator  codegen = CodeGenerator(statementsa);
    if(CheckScope(statementsa)){
        
        string x = "echo \"" + codegen.emitCode() + "\" >output.s";
        system(x.c_str());
        x = "nasm -felf64 output.s -o output.o";
        system(x.c_str());
        x = "ld output.o ./lib/printnumber.o -o output";
        system(x.c_str());
        x = "./output";
        system(x.c_str());
    }else{
        cout << "Invalid code";
    }
    

}

