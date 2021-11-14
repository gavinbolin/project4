#ifndef P1_HEADER_H
#define P1_HEADER_H
class Header{
private:
    std::vector<std::string> attributes;
public:
    Header(std::vector<std::string>& headers){attributes = headers;}
    size_t size(){return attributes.size();}
    std::string at(size_t i){return attributes[i];}
};
#endif //P1_HEADER_H
