#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QmarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "WhitespaceAutomaton.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    //delete automata and token vectors
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QmarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new WhitespaceAutomaton());
}

void Lexer::Run(std::string& input) {
    lineNum = 1;
    while(input.size() > 0) {
        maxRead = 0;
        maxAuto = automata[0];
        for (size_t i = 0; i < automata.size(); i++) {
            int inputRead = automata[i]->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAuto = automata[i];
                lineNum += automata[i]->NewLinesRead();
            }
        }
        if (maxRead > 0) {
            Token *newToken = maxAuto->CreateToken(input.substr(0, maxRead), lineNum-maxAuto->NewLinesRead()); //input string, line num
            if (newToken->notWhite() && newToken->notCom()){
                tokens.push_back(newToken);
            } else {
                //input.erase(maxRead,1);
                delete newToken;
            }
        } else {
            maxRead = 1;
            Token *newToken = new Token(TokenType::UNDEFINED,input.substr(0,1),lineNum); //input string, line num
            tokens.push_back(newToken);
        }
        input.erase(0, maxRead);
    }
    Token *eofToken = new Token(TokenType::END, "", lineNum);
    tokens.push_back(eofToken);
    /*for (size_t i = 0; i < tokens.size(); i++) {
        cout << tokens[i]->toString() << endl;
    }
    cout << "Total Tokens = " << tokens.size();*/
}