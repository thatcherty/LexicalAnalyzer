#pragma once
#include "lexeme.h"
#include <iostream>
#include <unordered_map>
#include <regex>
#include <vector>

using namespace std;

enum states { ID_OR_KEY, DIGIT, STRING_LIT, CHAR_LIT, DIV_OR_COMM, OPERATOR, DELIMITER, END };

class LexAnalyze
{
public:
    LexAnalyze();
    void lex(string& code);

    const vector<lexeme>& get_tokens() const { return tokens; }

private:
    states state;
    vector<lexeme> tokens{};
    unordered_map<states, regex> reg_ex;
};
