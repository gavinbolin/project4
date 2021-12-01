#ifndef P1_TUPLE_H
#define P1_TUPLE_H
class Tuple{
private:
    std::vector<std::string> values;
public:
    Tuple(const std::vector<std::string>& params){values = params;}
    bool operator<(const Tuple &rhs) const {return values < rhs.values;}
    bool operator==(const Tuple &rhs) const {return values == rhs.values;}
    std::string at(size_t i){return values[i];}
    size_t size(){return values.size();}
    void toString(){
        for(size_t i=0; i<values.size(); i++){
            cout << values[i];
            if(i != values.size()-1)
                cout << ", ";
            else cout << endl;
        }
    }
    bool isJoinable(Tuple t, std::vector<pair<size_t,size_t>> dup){
        for(auto i:dup){
            if(this->at(i.first) != t.at(i.second))
                return false;
        }
        return true;
    }
    Tuple combine(Tuple t1,Tuple t2, std::vector<pair<size_t, size_t>> dup){
        Tuple newT = t1;
        for(size_t i=0; i<t2.values.size(); i++){
            bool dupl = true;
            for(auto j:dup)
                if(i == j.second)
                    dupl = 0;
            if(dupl)
                newT.values.push_back(t2.values[i]);
        }
        return newT;
    }
};
#endif //P1_TUPLE_H
