#include "LexAnalyze.h"

int main()
{
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

	cout << "S. No." << " Lexeme " << " Token " << "Line No." << endl;

	for (int i = 0; i < tokens.size(); i++)
	{
		cout << i << ". " << tokens[i].type_to_string() << " " << tokens[i].val << " " << tokens[i].line << endl;
	}

	return 0;
}