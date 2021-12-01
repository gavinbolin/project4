#ifndef P1_HEADER_H
#define P1_HEADER_H
class Header{
private:
    std::vector<std::string> attributes;
public:
    Header(std::vector<std::string>& headers){attributes = headers;}
    size_t size(){return attributes.size();}
    std::string at(size_t i){return attributes[i];}
    std::vector<std::string> getVals(){return attributes;}
    void setHead(std::string s){attributes.push_back(s);}
};
#endif //P1_HEADER_H
