#ifndef P1_RELATION_H
#define P1_RELATION_H
#include "Tuple.h"
#include "Header.h"
class Relation{
private:
    std::string name;
    Header* head;
    std::set<Tuple> t = {};
public:
    Relation(){name = ""; head = NULL;}
    Relation(std::string n, Header* h){name = n; head = h;}
    std::vector<pair<size_t, size_t>> dup;

    void addTuple(Tuple newT){t.insert(newT);}
    void setName(std::string n){this->name = n;}
    std::string getName(){return name;}
    Header* getHead(){return head;}
    std::set<Tuple> getT(){return t;}
    void toString(){
        if(t.empty())
            cout << "No\n";
        else
            cout << "Yes(" <<t.size() << ")\n";
        for(auto i: t){
            if (head->size() != 0)
                cout << "  ";
            for(size_t j=0; j<head->size(); j++){
                cout << head->at(j) << '=' << i.at(j);
                if(j != head->size()-1)
                    cout << ", ";
                else
                    cout << '\n';
            }
        }
    }
    Relation* join(Relation* rel2){
        Header* h = this->head; //vector of sets of where both values were
        for (size_t i=0; i<rel2->head->size(); i++){
            bool found = 0;
            for(size_t j=0; j<this->head->size(); j++){
                if(rel2->head->at(i) == this->head->at(j)) {
                    dup.push_back(make_pair(j,i));
                    found = 1;
                }
            }
            if(!found) h->setHead(rel2->head->at(i));
        }
        Relation* temp = new Relation("temp", h);
        for(auto i:t){
            for(auto j:rel2->t){
                if(i.isJoinable(j,dup)){
                    temp->addTuple(i.combine(i,j,dup));
                }
            }
        }
        dup.clear();
        return temp;
    }
    bool unite(Relation* result){
        if(result->t.size() == 0)
            return false;
        bool pass = false;
        for(auto i:result->t){
            if(t.count(i) == 0) {
                this->addTuple(i);
                cout << "  ";
                for(size_t k=0; k<i.size(); k++) {
                    cout << result->getHead()->at(k) << "=" << i.at(k);
                    if (k != i.size() - 1)
                        cout << ", ";
                    else cout << endl;
                }
                pass = true;
            }
        } return pass;
    }
    /*void removeDup(Relation* relation){
        std::set<Tuple> newT;
        for(auto i:t) {
            if (relation->t.find(i) == t.end())
                newT.insert(i);
        } t = newT;
    }
    void ruleString(Relation* result){
        for(auto j:result->getT()){
            cout << "  ";
            for(size_t k=0; k<j.size(); k++) {
                cout << result->getHead()->at(k) << "=" << j.at(k);
                if (k != j.size() - 1)
                    cout << ", ";
                else cout << endl;
            }
        }
    }*/
    Relation* select1(size_t pos, std::string val){
        Relation* newTemp = new Relation(name, head);
        for(auto i: t){
            if(i.at(pos) == val)
                newTemp->addTuple(i);
        }
        return newTemp;
    }
    Relation* select2(size_t pos1, size_t pos2){
        Relation* newTemp = new Relation(name, head);
        for(auto i: t){
            if(i.at(pos1) == i.at(pos2))
                newTemp->addTuple(i);
        }
        return newTemp;
    }
    Relation* project(std::vector<int> col){
        Relation* newTemp = new Relation(name, head);
        for(auto i: t){
            std::vector<std::string> newT;
            for(size_t j=0; j<col.size(); j++){
                //if(i.at(j) == )
                newT.push_back(i.at(col[j]));
            }
            newTemp->addTuple(newT);
        }
        return newTemp;
    }
    Relation* rename(std::vector<std::string> h){ //void func to reset header to passed val
        head = new Header(h);
        Relation* newTemp = new Relation(name, head);
        for(auto i: t){
            newTemp->addTuple(i);
        }
        return newTemp;
    }
};
#endif //P1_RELATION_H

//cout << head->at(head->size()) + '=' + i.at(head->size()) + '\n';
/*std::string out;
for(auto i: t){
    for(size_t j=0; j<head->size(); j++){
        out += head->at(j) + '=' + i.at(j) + ", ";
    }
    out.pop_back();
    out.pop_back();
    out += '\n';
}
return out;*/
