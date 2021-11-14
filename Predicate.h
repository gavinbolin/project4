#ifndef P1_PREDICATE_H
#define P1_PREDICATE_H
#include "Parameter.h"

class Predicate{
private:
    std::string head;
    vector<Parameter*> params;
public:
    Predicate(std::string h, vector<Parameter*> p){head = h; params = p;}
    void toString(){
        cout << head << "(";
        for (size_t i=0; i < params.size(); i++){
            if(i != 0)
                cout << ",";
            params[i]->toString();
        }
    }
    std::vector<Parameter*> getParams(){return params;}
    std::string getName(){return head;}
    size_t pSize(){return params.size();}
    Parameter* at(size_t i){return params[i];}
    std::vector<std::string> makeTuple(){
        std::vector<std::string> out;
        for(size_t i=0; i<params.size(); i++){
            out.push_back(params[i]->getDesc());
        }
        return out;
    }
};
#endif //P1_PREDICATE_H
