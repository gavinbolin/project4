#ifndef P1_COMMAAUTOMATON_H
#define P1_COMMAAUTOMATON_H
#include "Automaton.h"

class CommaAutomaton : public Automaton
{
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {}

    void S0(const std::string& input) {
        if (input[index] == ',') {
            inputRead = 1;
        }
        else {
            Serr();
        }
    }
};

#endif //P1_COMMAAUTOMATON_H
