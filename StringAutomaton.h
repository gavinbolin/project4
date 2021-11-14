#ifndef P1_STRINGAUTOMATON_H
#define P1_STRINGAUTOMATON_H
#include "Automaton.h"

class StringAutomaton : public Automaton
{
private:
    void S1(const std::string& input) {
        while(true){
            if (input[index] == '\''){
                inputRead++;
                index++;
                S2(input);
                break;
            }
            if (index == input.size()){
                type = TokenType::UNDEFINED;
                break;
            }
            if (input[index] == '\n')
                newLines++;
            inputRead++;
            index++;
        }
    }
    void S2(const std::string &input){
        if (input[index] == '\''){
            inputRead++;
            index++;
            S1(input);
        }
    }

public:
    StringAutomaton() : Automaton(TokenType::STRING) {}

    void S0(const std::string& input) { //for loop
        if (input[index] == '\'') {
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }
};

#endif //P1_STRINGAUTOMATON_H
