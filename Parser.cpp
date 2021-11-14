#include "Parser.h"

Parser::Parser(){ index = 0; pass = true; isQ = false; }
Parser::~Parser(){}

DatalogProgram* Parser::Run(vector<Token*> tokens){
    try {
        if (tokens[index]->getType() == TokenType::SCHEMES)
            index++; else throw index;
        if (tokens[index]->getType() == TokenType::COLON)
            index++; else throw index;
        scheme(tokens);
        schemeList(tokens);
        if (tokens[index]->getType() == TokenType::FACTS)
            index++; else throw index;
        if (tokens[index]->getType() == TokenType::COLON)
            index++; else throw index;
        factList(tokens);
        if (tokens[index]->getType() == TokenType::RULES)
            index++; else throw index;
        if (tokens[index]->getType() == TokenType::COLON)
            index++; else throw index;
        ruleList(tokens);
        if (tokens[index]->getType() == TokenType::QUERIES)
            index++; else throw index;
        if (tokens[index]->getType() == TokenType::COLON)
            index++; else throw index;
        query(tokens);
        queryList(tokens);
        DatalogProgram* dlp = new DatalogProgram(vecS, vecF, vecR, vecQ);
        for (size_t i=0; i < domain.size(); i++){
            for (size_t j=0; j < domain.size(); j++){
                if (domain[i] == domain[j] && i != j)
                    domain[j].erase();
            }
        }
        vector<string> d;
        for (size_t i=0; i < domain.size(); i++)
            if (domain[i] != "")
                d.push_back(domain[i]);
        sort(d.begin(),d.end());
        dlp->setDomain(d);
        if (tokens[index]->getType() == TokenType::END)
            return dlp; else throw index;
    } catch(int i) {
        pass = false;
        cout << "Failure!\n  " << tokens[i]->toString();
    }
    return d;
}

void Parser::schemeList(vector<Token*> tokens){
    if (tokens[index]->getType() == TokenType::FACTS)
        return;
    scheme(tokens);
    if (tokens[index]->getType() == TokenType::ID)
        schemeList(tokens);
    else if (tokens[index]->getType() == TokenType::FACTS)
        return;
    else throw index;
}

void Parser::factList(vector<Token*> tokens){
    if (tokens[index]->getType() == TokenType::RULES)
        return;
    fact(tokens);
    if (tokens[index]->getType() == TokenType::ID)
        factList(tokens);
    else if (tokens[index]->getType() == TokenType::RULES)
        return;
    else throw index;
}

void Parser::ruleList(vector<Token*> tokens){
    if (tokens[index]->getType() == TokenType::QUERIES)
        return;
    rule(tokens);
    if (tokens[index]->getType() == TokenType::ID)
        ruleList(tokens);
    else if (tokens[index]->getType() == TokenType::QUERIES)
        return;
    else throw index;
}

void Parser::queryList(vector<Token*> tokens){
    if (tokens[index]->getType() == TokenType::END)
        return;
    query(tokens);
    if (tokens[index]->getType() == TokenType::ID)
        queryList(tokens);
    else if (tokens[index]->getType() == TokenType::END)
        return;
    else throw index;
}

void Parser::scheme(vector<Token*> tokens){
    string head;
    if (tokens[index]->getType() == TokenType::ID) { // add scheme head
        head = tokens[index]->getDesc();
        index++;
    }else throw index;
    if (tokens[index]->getType() == TokenType::LEFT_PAREN)
        index++; else throw index;
    temp.clear();
    if (tokens[index]->getType() == TokenType::ID){
        string id = tokens[index]->getDesc();
        Parameter* p = new Parameter(0,id);
        temp.push_back(p);
        index++;
    }else throw index;
    idList(tokens);
    if (tokens[index]->getType() == TokenType::RIGHT_PAREN)
        index++; else throw index;
    Predicate* p = new Predicate(head,temp);
    vecS.push_back(p);
}

void Parser::fact(vector<Token*> tokens){
    string head;
    if (tokens[index]->getType() == TokenType::ID) {
        head = tokens[index]->getDesc();
        index++;
    }else throw index;
    if (tokens[index]->getType() == TokenType::LEFT_PAREN)
        index++; else throw index;
    temp.clear();
    if (tokens[index]->getType() == TokenType::STRING){
        string str = tokens[index]->getDesc();
        domain.push_back(str);
        Parameter* p = new Parameter(1,str);
        temp.push_back(p);
        index++;
    }else throw index;
    stringList(tokens);
    if (tokens[index]->getType() == TokenType::RIGHT_PAREN)
        index++; else throw index;
    if (tokens[index]->getType() == TokenType::PERIOD)
        index++; else throw index;
    Predicate* p = new Predicate(head, temp);
    vecF.push_back(p);
}

void Parser::rule(vector<Token*> tokens){
    temp2.clear();
    Predicate* h = headPredicate(tokens);
    if (tokens[index]->getType() == TokenType::COLON_DASH)
        index++; else throw index;
    predicate(tokens);
    predicateList(tokens);
    if (tokens[index]->getType() == TokenType::PERIOD)
        index++; else throw index;
    Rule* r = new Rule(h,temp2);
    vecR.push_back(r);
}

void Parser::query(vector<Token*> tokens){
    isQ = true;
    predicate(tokens);
    if (tokens[index]->getType() == TokenType::Q_MARK)
        index++; else throw index;
}

Predicate* Parser::headPredicate(vector<Token*> tokens){
    string head;
    if (tokens[index]->getType() == TokenType::ID){
        head = tokens[index]->getDesc();
        index++;
    }else throw index;
    if (tokens[index]->getType() == TokenType::LEFT_PAREN)
        index++; else throw index;
    temp.clear();
    if (tokens[index]->getType() == TokenType::ID){
        string id = tokens[index]->getDesc();
        Parameter* p = new Parameter(0,id);
        temp.push_back(p);
        index++;
    }else throw index;
    idList(tokens);
    if (tokens[index]->getType() == TokenType::RIGHT_PAREN)
        index++; else throw index;
    Predicate* p = new Predicate(head,temp);
    return p;
}

void Parser::predicate(vector<Token *> tokens){
    string head;
    if (tokens[index]->getType() == TokenType::ID){
        head = tokens[index]->getDesc();
        index++;
    }else throw index;
    if (tokens[index]->getType() == TokenType::LEFT_PAREN)
        index++; else throw index;
    temp.clear();
    parameter(tokens);
    parameterList(tokens);
    if (tokens[index]->getType() == TokenType::RIGHT_PAREN)
        index++; else throw index;
    Predicate* p = new Predicate(head,temp);
    if (!isQ) temp2.push_back(p);
    if (isQ) vecQ.push_back(p);
}

void Parser::predicateList(vector<Token*> tokens){
    if (tokens[index]->getType() == TokenType::PERIOD)
        return;
    if (tokens[index]->getType() == TokenType::COMMA)
        index++; else throw index;
    predicate(tokens);
    if (tokens[index]->getType() == TokenType::COMMA)
        predicateList(tokens);
    if (tokens[index]->getType() == TokenType::PERIOD)
        return;
    else throw index;
}

void Parser::parameterList(vector<Token*> tokens){
    if (tokens[index]->getType() == TokenType::RIGHT_PAREN)
        return;
    if (tokens[index]->getType() == TokenType::COMMA)
        index++; else throw index;
    parameter(tokens);
    if (tokens[index]->getType() == TokenType::RIGHT_PAREN) // may fail if only one param
        return;
    if (tokens[index]->getType() == TokenType::COMMA)
        parameterList(tokens);
    else throw index;
}

void Parser::stringList(vector<Token*> tokens){
    if (tokens[index]->getType() == TokenType::RIGHT_PAREN)
        return;
    if (tokens[index]->getType() == TokenType::COMMA)
        index++; else throw index;
    if (tokens[index]->getType() == TokenType::STRING){
        string str = tokens[index]->getDesc();
        domain.push_back(str);
        Parameter* p = new Parameter(1,str);
        temp.push_back(p);
        index++;
    }else throw index;
    stringList(tokens);
}

void Parser::idList(vector<Token*> tokens){
    if (tokens[index]->getType() == TokenType::RIGHT_PAREN)
        return;
    if (tokens[index]->getType() == TokenType::COMMA)
        index++; else throw index;
    if (tokens[index]->getType() == TokenType::ID){
        string id = tokens[index]->getDesc();
        Parameter* p = new Parameter(0,id);
        temp.push_back(p);
        index++;
        }else throw index;
    idList(tokens);
}

void Parser::parameter(vector<Token*> tokens) {
    if (tokens[index]->getType() == TokenType::STRING){
        string str = tokens[index]->getDesc();
        Parameter* p = new Parameter(1,str);
        temp.push_back(p);
        index++;
    }else if (tokens[index]->getType() == TokenType::ID){
        string id = tokens[index]->getDesc();
        Parameter* p = new Parameter(0,id);
        temp.push_back(p);
        index++;
    }else throw index;
}

//pass through all grammar productions
/*for (index = 0; index < tokens.size(); index++){
    if (tokens[index]->getType() == TokenType::UNDEFINED)
        throw index;
    else if (tokens[index]->getType() == TokenType::COMMENT)
        continue;
    else if (tokens[index]->getType() == TokenType::COLON);
    else if (tokens[index]->getType() == TokenType::COLON_DASH);
    else if (tokens[index]->getType() == TokenType::PERIOD);
    else if (tokens[index]->getType() == TokenType::Q_MARK);
    else if (tokens[index]->getType() == TokenType::LEFT_PAREN);
    else if (tokens[index]->getType() == TokenType::RIGHT_PAREN);
    else if (tokens[index]->getType() == TokenType::MULTIPLY);
    else if (tokens[index]->getType() == TokenType::ADD); */