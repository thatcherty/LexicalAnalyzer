#pragma once
#include <string>

using namespace std;

// Token types used by the lexer.
enum types {
    KEYWORD,
    ID,
    NUMBER,
    STRING,
    CHAR,

    // Delimiters
    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    COMMA,
    SEMICOLON,

    // Operators
    EQUALS,        // =
    GREATER,       // >
    PLUSEQUAL,     // +=
    MINUSEQUAL,    // -=
    NOTEQUAL,      // !=
    DIV,           // /

    END_OF_FILE,
    UNKNOWN
};

class lexeme
{
public:
    lexeme(types t, string s);
    string type_to_string();

    types type;
    string val;

    int line = 1;
    int col = 1;
};
