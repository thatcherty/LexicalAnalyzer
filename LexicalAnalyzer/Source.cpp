#include "LexAnalyze.h"
#include <iomanip>


int main()
{
    // Column widths
    const int W_SN = 8;
    const int W_LEX = 18;
    const int W_TOKEN = 18;
    const int W_LINE = 10;

	string code = "int calculate() {\n"
		" int count = 0, value = 10;\n"
		" for (; value > count;) {\n"
		" count += 2; /* Increment count by 2 */\n"
		" }\n"
		" return count;\n"
		"}\n";
	
	LexAnalyze lexer = LexAnalyze();

	lexer.lex(code);

	vector<lexeme> tokens = lexer.get_tokens();

    // Header
    cout << left
        << setw(W_SN) << "S. No."
        << setw(W_LEX) << "Lexeme"
        << setw(W_TOKEN) << "Token"
        << setw(W_LINE) << "Line No."
        << "\n";

    // Divider
    cout << std::string(W_SN + W_LEX + W_TOKEN + W_LINE, '-') << "\n";

    // Rows
    for (size_t i = 0; i < tokens.size(); i++)
    {


        cout << left
            << setw(W_SN) << (std::to_string(i + 1) + ".")
            << setw(W_LEX) << tokens[i].val
            << setw(W_TOKEN) << tokens[i].type_to_string()
            << setw(W_LINE) << tokens[i].line
            << "\n";
    }

	return 0;
}