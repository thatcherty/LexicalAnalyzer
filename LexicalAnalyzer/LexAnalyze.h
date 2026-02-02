#pragma once
#include "lexeme.h"
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class LexAnalyze
{
public:
    LexAnalyze();
    void lex(string& code);
    const vector<lexeme>& get_tokens() const { return tokens; }

private:
    vector<lexeme> tokens{};
};
