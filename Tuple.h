#ifndef P1_TUPLE_H
#define P1_TUPLE_H
class Tuple{
private:
    std::vector<std::string> values;
public:
    Tuple(const std::vector<std::string>& params){
        values = params;
    }
    bool operator<(const Tuple &rhs) const {
        return values < rhs.values;
    }
    string toString(){
        std::string contents;
        for(const auto& i: values) {
            contents += i + ' ';
        }
        return contents;
    }
    std::string at(size_t i){return values[i];}
};
#endif //P1_TUPLE_H
