#include "LexAnalyze.h"

// helper functions
static bool is_alpha_(char c)
{
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '_';
}

static bool is_alnum_(char c)
{
    return is_alpha_(c) || (c >= '0' && c <= '9');
}

static bool is_digit_(char c)
{
    return (c >= '0' && c <= '9');
}

static bool is_whitespace_(char c)
{
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v';
}

static bool is_keyword_(const string& s)
{
    // Extend this set as needed for your language.
    static const unordered_map<string, bool> keywords{
        {"int", true}, {"for", true}, {"if", true}, {"else", true}, {"return", true}
    };
    return keywords.find(s) != keywords.end();
}

LexAnalyze::LexAnalyze()
{
    reg_ex.emplace(ID_OR_KEY, regex(R"([A-Za-z_])"));
    reg_ex.emplace(DIGIT, regex(R"([0-9])"));

    state = ID_OR_KEY;
}

void LexAnalyze::lex(string& code)
{
    tokens.clear();

    int line = 1;
    int col = 1;

    auto push_tok = [&](types t, const string& v, int l, int c) {
        lexeme lx(t, v);
        lx.line = l;
        lx.col = c;
        tokens.push_back(lx);
        };

    const auto peek = [&](size_t i, size_t ahead = 0) -> char {
        size_t idx = i + ahead;
        if (idx >= code.size()) return '\0';
        return code[idx];
        };

    for (size_t i = 0; i < code.size();)
    {
        char c = peek(i);

        // Skip whitespace (but track line/col)
        if (is_whitespace_(c))
        {
            if (c == '\n') { line++; col = 1; }
            else { col++; }
            i++;
            continue;
        }

        // Comments or division
        if (c == '/')
        {
            char n = peek(i, 1);

            // Line comment: // ... \n
            if (n == '/')
            {
                i += 2;
                col += 2;
                while (i < code.size() && peek(i) != '\n')
                {
                    i++; col++;
                }
                continue;
            }

            // Block comment: /* ... */
            if (n == '*')
            {
                i += 2;
                col += 2;
                while (i < code.size())
                {
                    if (peek(i) == '\n') { line++; col = 1; i++; continue; }
                    if (peek(i) == '*' && peek(i, 1) == '/')
                    {
                        i += 2;
                        col += 2;
                        break;
                    }
                    i++; col++;
                }
                continue;
            }

            // If you want DIV as a token later, add it to enum types.
            push_tok(UNKNOWN, "/", line, col);
            i++; col++;
            continue;
        }

        // Identifier or keyword
        if (is_alpha_(c))
        {
            int start_col = col;
            string s;
            while (i < code.size() && is_alnum_(peek(i)))
            {
                s.push_back(peek(i));
                i++; col++;
            }

            if (is_keyword_(s)) push_tok(KEYWORD, s, line, start_col);
            else                push_tok(ID, s, line, start_col);
            continue;
        }

        // Number (integer for now)
        if (is_digit_(c))
        {
            int start_col = col;
            string s;
            while (i < code.size() && is_digit_(peek(i)))
            {
                s.push_back(peek(i));
                i++; col++;
            }
            push_tok(NUMBER, s, line, start_col);
            continue;
        }

        // String literal "..."
        if (c == '"')
        {
            int start_col = col;
            string s;
            s.push_back('"');
            i++; col++;

            while (i < code.size())
            {
                char ch = peek(i);

                // Allow escapes: \" \\ \n etc
                if (ch == '\\' && peek(i, 1) != '\0')
                {
                    s.push_back(peek(i));
                    s.push_back(peek(i, 1));
                    i += 2;
                    col += 2;
                    continue;
                }

                s.push_back(ch);
                i++; col++;

                if (ch == '"') break;
                if (ch == '\n') { line++; col = 1; } // in case of bad multiline string
            }

            push_tok(STRING, s, line, start_col);
            continue;
        }

        // Char literal 'a' or '\n'
        if (c == '\'')
        {
            int start_col = col;
            string s;
            s.push_back('\'');
            i++; col++;

            while (i < code.size())
            {
                char ch = peek(i);

                if (ch == '\\' && peek(i, 1) != '\0')
                {
                    s.push_back(peek(i));
                    s.push_back(peek(i, 1));
                    i += 2;
                    col += 2;
                    continue;
                }

                s.push_back(ch);
                i++; col++;

                if (ch == '\'') break;
                if (ch == '\n') { line++; col = 1; }
            }

            push_tok(CHAR, s, line, start_col);
            continue;
        }

        // Multi-char operators first (maximal munch)
        {
            int start_col = col;

            // !=
            if (c == '!' && peek(i, 1) == '=')
            {
                push_tok(NOTEQUAL, "!=", line, start_col);
                i += 2; col += 2;
                continue;
            }

            // +=
            if (c == '+' && peek(i, 1) == '=')
            {
                push_tok(PLUSEQUAL, "+=", line, start_col);
                i += 2; col += 2;
                continue;
            }

            // -=
            if (c == '-' && peek(i, 1) == '=')
            {
                push_tok(MINUSEQUAL, "-=", line, start_col);
                i += 2; col += 2;
                continue;
            }
        }

        // Single-char delimiters / operators
        {
            int start_col = col;
            switch (c)
            {
            case '(':
                push_tok(LPAREN, "(", line, start_col);
                break;
            case ')':
                push_tok(RPAREN, ")", line, start_col);
                break;
            case '{':
                push_tok(LBRACE, "{", line, start_col);
                break;
            case '}':
                push_tok(RBRACE, "}", line, start_col);
                break;
            case ',':
                push_tok(COMMA, ",", line, start_col);
                break;
            case ';':
                push_tok(SEMICOLON, ";", line, start_col);
                break;
            case '=':
                push_tok(EQUALS, "=", line, start_col);
                break;
            case '>':
                push_tok(GREATER, ">", line, start_col);
                break;
            default:
                // Unknown character
                push_tok(UNKNOWN, string(1, c), line, start_col);
                break;
            }
            i++; col++;
            continue;
        }
    }

}
