#ifndef P1_MULTIPLYAUTOMATON_H
#define P1_MULTIPLYAUTOMATON_H
#include "Automaton.h"

class MultiplyAutomaton : public Automaton
{
public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}

    void S0(const std::string& input) {
        if (input[index] == '*') {
            inputRead = 1;
        }
        else {
            Serr();
        }
    }
};

#endif //P1_MULTIPLYAUTOMATON_H
