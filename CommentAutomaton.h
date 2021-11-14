#ifndef P1_COMMENTAUTOMATON_H
#define P1_COMMENTAUTOMATON_H
#include "Automaton.h"
#include <string>

class CommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input) {
        while(true) {
            if (input[index] == '\n')
                break;
            inputRead++;
            index++;
        }
        /*while(input[index] != '\n' && input[index] != EOF){
            inputRead++;
            index++;
        } //input.erase(inputRead-1,1);
        //inputRead++;
        //newLines++;*/
    }
    void S2(const std::string& input){
        while(true){
            if (input[index] == '|'){
                inputRead++;
                index++;
                S3(input);
                break;
            }
            if (index == input.size()){
                type = TokenType::UNDEFINED;
                newLines++;
                break;
            }
            if (input[index] == '\n')
                newLines++;
            inputRead++;
            index++;
        }
    }
    void S3(const std::string& input){
        if (input[index] == '#'){
            inputRead++;
        } else {
            inputRead++;
            index++;
            S2(input);
        }
    }

public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}

    void S0(const std::string& input) { //for loop
        if (input[index] == '#' && input[index+1] == '|') {
            inputRead+=2;
            index+=2;
            S2(input);
        }
        else if (input[index] == '#') {
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }
};

#endif //P1_COMMENTAUTOMATON_H
