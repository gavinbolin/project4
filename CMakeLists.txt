cmake_minimum_required(VERSION 3.16.3)
project(p1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(p1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        main.cpp
        Token.cpp
        Token.h CommaAutomaton.h
        PeriodAutomaton.h
        QmarkAutomaton.h
        LeftParenAutomaton.h
        RightParenAutomaton.h
        MultiplyAutomaton.h
        AddAutomaton.h
        SchemesAutomaton.h
        FactsAutomaton.h
        RulesAutomaton.h
        QueriesAutomaton.h
        WhitespaceAutomaton.h
        IDAutomaton.h
        StringAutomaton.h
        CommentAutomaton.h Parser.h Parser.cpp DatalogProgram.h Parameter.h Predicate.h Rule.h Tuple.h Header.h Relation.h Database.h Interpreter.h)
