#ifndef crap_lexer_h
#define crap_lexer_h
#include "common.h"

typedef enum {
	OR,
	AND,
	IDENTIFIER,
	LT,
	LTE,
	GTE,
	GT,
	EQUALSEQUALS,
	ASSIGNMENT,
	IF,
	WHILE,
	FOR,
	ELSE,
	SEMICOLON,
	MINUS,
	PLUS,
	TIMES,
	PRINT,
	LB,
	RB,
	NUMBER,
	LBRACE, 
	RBRACE,
	BANGEQUALS,
	NOT,
} TokenType;
map<TokenType,string> tokennames {{OR,"||"},{AND,"&&"},{IDENTIFIER,"IDENTIFIER"},{LT,"LESS THAN"},{LTE,"LESS THAN OR EQUAL"},{GTE,"GREATER THAN OR EQUAL"},{GT,"GREATER THAN"},{EQUALSEQUALS,"EQUALSEQUALS"},{ASSIGNMENT,"ASSIGN"},
{IF,"IF"},{WHILE,"WHILE"},{FOR,"FOR"},{ELSE,"ELSE"},{SEMICOLON,"SEMICOLON"},{MINUS,"MINUS"},{PLUS,"PLUS"},{TIMES,"TIMES"},{PRINT,"PRINT"},{LB,"LEFTBRACKET"},{RB,"RIGHTBRACKET"},{NUMBER,"NUM"},{LBRACE,"LBRACE"},{RBRACE,"RBRACE"},{"BANGEQUALS",BANGEQUALS},{"NOT",NOT}};
map<string,TokenType> keywords ={{"for",FOR},{"while",WHILE},{"if",IF},{"or",OR},{"and",AND},{"else",ELSE},{"print",PRINT}};
typedef struct {
	TokenType type;
	int value;
	string name;
}	Token;
class Lexer {
	public:
		int inputpointer;
		string input;
		Lexer(string initialinput);
		vector<Token> tokenize();
		bool isNum();
		bool isAlphaNumeric();
		bool isCharacter();
		Token Identifier();
		Token Number();
};
#endif
