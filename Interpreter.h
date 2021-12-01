#ifndef P1_INTERPRETER_H
#define P1_INTERPRETER_H
#include "DatalogProgram.h"
#include "Relation.h"
class Interpreter{
private:
    DatalogProgram* dlp;
    std::vector<Relation*> relations;
    std::vector<Relation*> results; //vec of relations produced by queries
    size_t rounds = 0;
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
        std::vector<Rule*> rules = dlp->getR(); //list out new tuples made, also track number of loops
        cout << "Rule Evaluation\n";
        while(evalRules(rules));
        cout << "\nSchemes populated after " << rounds << " passes through the Rules.\n\n";

        std::vector<Predicate*> queries = dlp->getQ();
        cout << "Query Evaluation\n";
        for(size_t i=0; i<queries.size(); i++){
            for(size_t j=0; j<relations.size(); j++){
                if(queries[i]->getName() == relations[j]->getName()){
                    Relation* rel = evalPred(relations[j], queries[i]);
                    results.push_back(rel);
                    queries[i]->toString();
                    cout << ")? ";
                    results[i]->toString();
                } //like headers joined in join function
            }
        } //for loop for all queries, assign rel to header that matches
    }

    bool evalRules(std::vector<Rule*> rules){ //make sure the individual rule values are checked for differences?
        bool redo = false; // make relations only output changes once, make only changes inside for loop and output values
        for(size_t i=0; i<rules.size(); i++){ //loop of all the rules given
            std::vector<Relation*> temp;
            for(size_t j=0; j<rules[i]->pSize(); j++){ // matches rules with relations and adds params for the rule to temp
                for(size_t k=0; k<relations.size(); k++) {
                    if(rules[i]->at(j)->getName() == relations[k]->getName()){
                        temp.push_back(evalPred(relations[k], rules[i]->at(j)));
                    } //for each pred in each rule match with a relation
                }
            }
            for (size_t j=1; j<temp.size(); j++){ //joins each in temp to the first and sets result equal to it
                temp[0] = temp[0]->join(temp[j]);
            } Relation* result = temp[0];
            std::vector<int> pos;
            std::vector<std::string> val;
            for(size_t j=0; j<rules[i]->getHead()->pSize(); j++){ //get duplicate headers
                for(size_t k=0; k<result->getHead()->size(); k++){
                    if(rules[i]->getHead()->at(j)->getDesc() == result->getHead()->at(k))
                        pos.push_back(k);
                }
            }
            for(size_t j=0; j<relations.size(); j++){ //sets val to the relation that matches the rule head
                if(rules[i]->getHead()->getName() == relations.at(j)->getName())
                    val = relations.at(j)->getHead()->getVals();
            }
            result = result->project(pos);
            result = result->rename(val);
            result->setName(rules[i]->getHead()->getName());
            rules[i]->toString();
            for(size_t j=0; j<relations.size(); j++){ //loops relations to unite results
                //if(relations.at(j)->getName() == result->getName())  );
                if(relations.at(j)->getName() == result->getName()) {
                    //result->removeDup(relations.at(j));
                    if (relations.at(j)->unite(result)) {
                        //ruleString(result);
                        redo = true;
                    }
                }
            }
        } rounds++;
        return redo;
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
