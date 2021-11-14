#ifndef P1_WHITESPACEAUTOMATON_H
#define P1_WHITESPACEAUTOMATON_H
#include "Automaton.h"

class WhitespaceAutomaton : public Automaton
{
public:
    WhitespaceAutomaton() : Automaton(TokenType::WHITE) {}

    void S0(const std::string& input) {
        if (input[index] == ' ' || input[index] == '\t') {
            inputRead = 1;
        }
        else if (input[index] == '\n') {
            inputRead = 1;
            newLines++;
        }
        else {
            Serr();
        }
    }
};

#endif //P1_WHITESPACEAUTOMATON_H
