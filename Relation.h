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
    void addTuple(Tuple newT){t.insert(newT);}
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
            //cout << head->at(head->size()) + '=' + i.at(head->size()) + '\n';
        }

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
    }
    std::string getName(){return name;}
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
