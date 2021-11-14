#ifndef P1_DATALOGPROGRAM_H
#define P1_DATALOGPROGRAM_H
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram{
private:
    std::vector<Predicate*> vecS;
    std::vector<Predicate*> vecF;
    std::vector<Rule*> vecR;
    std::vector<Predicate*> vecQ;
    vector<string> domain;
public:
    DatalogProgram(vector<Predicate*> s, vector<Predicate*> f, vector<Rule*> r, vector<Predicate*> q){
        this->vecS = s;
        this->vecF = f;
        this->vecR = r;
        this->vecQ = q;
    }
    ~DatalogProgram();
    void setDomain(vector<string> v){this->domain = v;}
    std::vector<Predicate*> getS(){return vecS;}
    std::vector<Predicate*> getF(){return vecF;}
    std::vector<Rule*> getR(){return vecR;}
    std::vector<Predicate*> getQ(){return vecQ;}
    void toString(){
        cout << "Schemes(" << vecS.size() << "):\n";
        for (size_t i=0; i < vecS.size(); i++){
            cout << "  ";
            vecS[i]->toString();
            cout << ")\n";
        }
        cout << "Facts(" << vecF.size() << "):\n";
        for (size_t i=0; i < vecF.size(); i++){
            cout << "  ";
            vecF[i]->toString();
            cout << ").\n";
        }
        cout << "Rules(" << vecR.size() << "):\n";
        for (size_t i=0; i < vecR.size(); i++) {
            vecR[i]->toString();
            cout << ".\n";
        }
        cout << "Queries(" << vecQ.size() << "):\n";
        for (size_t i=0; i < vecQ.size(); i++){
            cout << "  ";
            vecQ[i]->toString();
            cout << ")?\n";
        }
        cout << "Domain(" <<domain.size() << "):\n";
        for (size_t i=0; i < domain.size(); i++)
            cout << "  " << domain[i] << endl;
    }
};
#endif //P1_DATALOGPROGRAM_H
