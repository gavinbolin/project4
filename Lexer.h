#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
    int lineNum;
    int maxRead;
    Automaton* maxAuto;

    void CreateAutomata();

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);
    vector<Token*> getTokens() { return tokens; }
    //Token*
};
#endif // LEXER_H

