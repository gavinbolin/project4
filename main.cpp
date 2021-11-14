#include <iostream>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "DatalogProgram.h"
#include "Interpreter.h"
using namespace std;

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();
    Parser* parser = new Parser();

    if (argc != 2) { return 1; }
    ifstream in(argv[1]);
    if (!in.is_open()) { return 1; }
    string input;
    for (string line; getline(in, line);) {
        input.append(line);
        input.append("\n");
    }
    lexer->Run(input);
    vector<Token*> tokens = lexer->getTokens();
    DatalogProgram* dlp = parser->Run(tokens);
    /*if (parser->getPass()) {
        cout << "Success!\n";
        dlp->toString();
    }*/
    Interpreter* inter = new Interpreter(dlp);
    inter->run();
    delete lexer;
    delete parser;
    return 0;
}