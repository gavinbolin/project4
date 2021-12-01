#ifndef P1_RULE_H
#define P1_RULE_H
#include "Predicate.h"

class Rule{
private:
    Predicate* head;
    vector<Predicate*> preds;
public:
    Rule(Predicate* h, vector<Predicate*> p){head = h; preds = p;}
    Predicate* getHead(){return head;}
    size_t pSize(){return preds.size();}
    Predicate* at(size_t i){return preds[i];}
    void toString(){
        head->toString();
        cout << ") :- ";
        for (size_t i=0; i < preds.size(); i++){
            preds[i]->toString();
            cout << ")";
            if (i != preds.size()-1)
                cout << ",";
        } cout << "." << endl;
    }
};
#endif //P1_RULE_H
