#include "../headers/scope.h"


vector<Expression*>* FindExpressions(Statement* statements){
    if(statements){

    switch(statements->statementtype){
        case STATCOMPOUND:{
         
            vector<Expression* >* assignexpr = new vector<Expression*> {};
            for(auto x:(*FindExpressions(statements->currentstatement))){
                    assignexpr->push_back(x);
                }
        
            vector<Expression* >* stuff = FindExpressions(statements->nextstatements);
            if(stuff){
            for(auto x:(*stuff)){
                assignexpr->push_back(x);
            }
            }
            
            return assignexpr;
            break;
        }
        case STATPRINT:{
            vector<Expression*>* printexpr = new vector<Expression*> {statements->expression};
            return printexpr;
            break;
        }
        case STATASSIGN:{
     
            vector<Expression*>* assignexpr = new vector<Expression*> {statements->expression};
    
            return assignexpr;
            break;
        }
        case STATIFELSE:{
            vector<Expression*>* assignexpr = new vector<Expression*> {statements->condition};

            for(auto x:(*FindExpressions(statements->valid))){
                assignexpr->push_back(x);
            }
            for(auto x:*FindExpressions(statements->invalid)){
                assignexpr->push_back(x);
            }
            return assignexpr;
            break;
        }
        case STATIF:{
            vector<Expression*>* assignexpr = new vector<Expression*> {statements->condition};

            for(auto x:(*FindExpressions(statements->statements))){
                assignexpr->push_back(x);
            }
       
            return assignexpr;
            break;
        }
        case STATFOR:{
            vector<Expression*>* assignexpr = new vector<Expression*> {};
              for(auto x:(*FindExpressions(statements->initializer))){
                assignexpr->push_back(x);
            }
            assignexpr->push_back(statements->condition);
            for(auto x:(*FindExpressions(statements->next))){
                assignexpr->push_back(x);
            }
            for(auto x:(*FindExpressions(statements->statements))){
                assignexpr->push_back(x);
            }
            return assignexpr;
            break;
        }
        case STATWHILE:{
            vector<Expression*>* assignexpr = new vector<Expression*> {statements->condition};
            for(auto x:(*FindExpressions(statements->statements))){
                assignexpr->push_back(x);
            }
            return assignexpr;
            break;
        }
    }
    }else{
        vector<Expression*>* assignexpr = new vector <Expression*> {};
        return assignexpr;
    }
}
vector<string>* GetIdentifiers(Expression* expression){
    vector<string>* assignexpr = new vector<string> {};

    if(expression){

        switch(expression->expressiontype){
            case EXPRIDENTIFIER:{

                assignexpr->push_back(expression->identifier);  
                break;
          }
            case EXPRBINARYOP:{
                for(auto x:(*GetIdentifiers(expression->expr1))){

                    assignexpr->push_back(x);
                }
                for(auto x:(*GetIdentifiers(expression->expr2))){

                    assignexpr->push_back(x);
                }
                break;
            }
            default:{
                break;
            }
        }
    }else{

        return assignexpr;
    }

    return assignexpr; 

} 
bool CheckScope(Statement* statements){
    vector<Expression*>* stuff;
    stuff = FindExpressions(statements);

    if(stuff){
    for(auto x:*stuff){
        vector<string>* identifiers = GetIdentifiers(x);
        if(identifiers){
        
        for(auto y:*identifiers){
            if(((x->symboltable).maintable).find(y) == (x->symboltable).maintable.end()){
                return false;
            }
        }
        }
    }
    }
    return true;
}

