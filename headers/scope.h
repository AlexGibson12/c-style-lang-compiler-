#ifndef crap_scope_h
#define crap_scope_h
#include "ast.h"
vector<Expression*>* FindExpressions(Statement* statements);
vector<string>* GetIdentifiers(Expression* expression);
bool CheckScope(Statement* statements);
#endif