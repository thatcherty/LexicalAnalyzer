#include "lexeme.h"

lexeme::lexeme(types t, string s)
{
	type = t;
	val = s;
}

string lexeme::type_to_string()
{
    switch (type)
    {
    case KEYWORD:      return "KEYWORD";
    case ID:           return "ID";
    case NUMBER:       return "NUMBER";
    case STRING:       return "STRING";
    case CHAR:         return "CHAR";
    case LPAREN:       return "LPAREN";
    case RPAREN:       return "RPAREN";
    case LBRACE:       return "LBRACE";
    case RBRACE:       return "RBRACE";
    case COMMA:        return "COMMA";
    case SEMICOLON:    return "SEMICOLON";
    case EQUALS:       return "EQUALS";
    case GREATER:      return "GREATER";
    case PLUSEQUAL:    return "PLUSEQUAL";
    case MINUSEQUAL:   return "MINUSEQUAL";
    case NOTEQUAL:     return "NOTEQUAL";
    case UNKNOWN:      return "UNKNOWN";
    default:           return "INVALID";
    }
}
