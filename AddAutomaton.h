#ifndef P1_ADDAUTOMATON_H
#define P1_ADDAUTOMATON_H
#include "Automaton.h"

class AddAutomaton : public Automaton
{
public:
    AddAutomaton() : Automaton(TokenType::ADD) {}

    void S0(const std::string& input) {
        if (input[index] == '+') {
            inputRead = 1;
        }
        else {
            Serr();
        }
    }
};

#endif //P1_ADDAUTOMATON_H
