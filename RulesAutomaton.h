#ifndef P1_RULESAUTOMATON_H
#define P1_RULESAUTOMATON_H
#include "Automaton.h"

class RulesAutomaton : public Automaton
{
private:
    void S1(const std::string& input) {
        if (input[index] == 'u') {
            inputRead++;
            index++;
            S2(input);
        } else {
            Serr();
        }
    }
    void S2(const std::string& input) {
        if (input[index] == 'l') {
            inputRead++;
            index++;
            S3(input);
        } else {
            Serr();
        }
    }
    void S3(const std::string& input) {
        if (input[index] == 'e') {
            inputRead++;
            index++;
            S4(input);
        } else {
            Serr();
        }
    }
    void S4(const std::string& input) {
        if (input[index] == 's') {
            inputRead++;
        } else {
            Serr();
        }
    }

public:
    RulesAutomaton() : Automaton(TokenType::RULES) {}

    void S0(const std::string& input) { //for loop
        if (input[index] == 'R') {
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }
};

#endif //P1_RULESAUTOMATON_H
