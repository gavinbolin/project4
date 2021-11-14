#ifndef P1_PARSER_H
#define P1_PARSER_H
#include <vector>
#include <bits/stdc++.h>
#include "Token.h"
#include "DatalogProgram.h"

class Parser
{
private:
    int index;
    bool pass;

public:
    vector<Predicate*> vecS;
    vector<Predicate*> vecF;
    vector<Rule*> vecR;
    vector<Predicate*> vecQ;
    vector<Parameter*> temp;
    vector<Predicate*> temp2;
    vector<string> domain;
    bool isQ;
    DatalogProgram* d = new DatalogProgram(vecS,vecF,vecR,vecQ);

    Parser();
    ~Parser();
    bool getPass(){ return pass; }
    DatalogProgram* Run(vector<Token*> tokens);
    void schemeList(vector<Token*> tokens);
    void factList(vector<Token*> tokens);
    void ruleList(vector<Token*> tokens);
    void queryList(vector<Token*> tokens);
    void scheme(vector<Token*> tokens);
    void fact(vector<Token*> tokens);
    void rule(vector<Token*> tokens);
    void query(vector<Token*> tokens);
    Predicate* headPredicate(vector<Token*> tokens);
    void predicate(vector<Token*> tokens);
    void predicateList(vector<Token*> tokens);
    void parameterList(vector<Token*> tokens);
    void stringList(vector<Token*> tokens);
    void idList(vector<Token*> tokens);
    void parameter(vector<Token*> tokens);
};
#endif
