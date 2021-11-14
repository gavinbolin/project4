#ifndef P1_IDAUTOMATON_H
#define P1_IDAUTOMATON_H
#include "Automaton.h"

class IDAutomaton : public Automaton
{
private:
    void S1(const std::string& input) {
        if (isalpha(input[index]) || isdigit(input[index])) {
            inputRead++;
            index++;
            S1(input);
        }
    }

public:
    IDAutomaton() : Automaton(TokenType::ID) {}

    void S0(const std::string& input) { //for loop
        if (isalpha(input[index])) {
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }
};

#endif //P1_IDAUTOMATON_H
