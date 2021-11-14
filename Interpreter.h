#ifndef P1_INTERPRETER_H
#define P1_INTERPRETER_H
#include "DatalogProgram.h"
#include "Relation.h"
class Interpreter{
private:
    DatalogProgram* dlp;
    std::vector<Relation*> relations;
    std::vector<Relation*> results; //vec of relations produced by queries
public:
    Interpreter(DatalogProgram* d){dlp = d;}
    void run(){
        std::vector<Predicate*> schemes = dlp->getS();
        for(size_t i=0; i<schemes.size(); i++){
            std::string name = schemes[i]->getName();
            std::vector<std::string> attributes;
            for(size_t j=0; j<schemes[i]->pSize(); j++){
                string desc = schemes[i]->at(j)->getDesc();
                attributes.push_back(desc);
            }
            Header* head = new Header(attributes);
            Relation* rel = new Relation(name, head);
            relations.push_back(rel);
        }
        std::vector<Predicate*> facts = dlp->getF();
        for(size_t i=0; i<facts.size(); i++){
            for(size_t j=0; j<relations.size(); j++){
                if (facts[i]->getName() == relations[j]->getName()){
                    relations[j]->addTuple(facts[i]->makeTuple());
                }
            }
        }
        std::vector<Predicate*> queries = dlp->getQ();
        for(size_t i=0; i<queries.size(); i++){
            for(size_t j=0; j<relations.size(); j++){
                if(queries[i]->getName() == relations[j]->getName()){
                    Relation* rel = evalPred(relations[j], queries[i]);
                    results.push_back(rel);
                    queries[i]->toString();
                    cout << ")? ";
                    results[i]->toString();
                }
            }
        } //for loop for all queries, assign rel to header that matches
    }
    Relation* evalPred(Relation* rel, Predicate* query){
        std::vector<int> pos;
        std::vector<std::string> val;
        Relation* temp = rel;
        for(size_t i=0; i<query->pSize(); i++){
            if(query->at(i)->constant()){
                temp = temp->select1(i, query->at(i)->getDesc());  //select1() use new rel, pos of header in question, and value in column in question
            } else {
                int seen = -1;
                for(size_t j=0; j<val.size(); j++){
                    if(query->at(i)->getDesc() == val[j]) //have seen this variable already
                        seen = j;
                }
                if(seen != -1){
                    temp = temp->select2(pos[seen], i);  //given two positions, both values need to have the same values
                } else {
                    val.push_back(query->at(i)->getDesc());
                    pos.push_back(i);
                }
            }
        }
        temp = temp->project(pos);
        temp = temp->rename(val);
        return temp; //delete? schemes facts queries
    }
};
#endif //P1_INTERPRETER_H
