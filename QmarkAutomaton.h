#ifndef P1_QMARKAUTOMATON_H
#define P1_QMARKAUTOMATON_H
#include "Automaton.h"

class QmarkAutomaton : public Automaton
{
public:
    QmarkAutomaton() : Automaton(TokenType::Q_MARK) {}

    void S0(const std::string& input) {
        if (input[index] == '?') {
            inputRead = 1;
        }
        else {
            Serr();
        }
    }
};

#endif //P1_QMARKAUTOMATON_H
